#include "StaffExp.h"

namespace Patch
{
    void StaffExp::InstallPatch() {
        if(settings.stavesGrantExperience)
        {
            REL::Relocation<uintptr_t> enchantmentItemVtable{ RE::VTABLE_EnchantmentItem[0] }; // EnchantmentItem::VirtualFunctionTable, index 0x60 contains GetSkillUsageData
            StaffExp::originalEnchantmentGetSkillData_ = enchantmentItemVtable.write_vfunc(0x60, StaffExp::EnchantmentGetSkillData);
            REL::Relocation<uintptr_t> spellItemVtable{ RE::VTABLE_SpellItem[0] }; // SpellItem::VirtualFunctionTable, index 0x60 contains GetSkillUsageData
            StaffExp::spellItemGetSkillData_ = reinterpret_cast<decltype(StaffExp::spellItemGetSkillData_)>(reinterpret_cast<std::uintptr_t*>(spellItemVtable.address())[0x60]);
            logger::info("\"Staves grant experience\" patch installed!");
            if (settings.staffExperienceIgnoresEnchantmentCost)
            {
                logger::info("\"Staff experience ignores enchantment cost\" patch installed!");
            }
            else
            {
                logger::info("\"Staff experience ignores enchantment cost\" patch is NOT enabled... skipping.");
            }
        }
        else
        {
            logger::info("\"Staves grant experience\" patch is NOT enabled... skipping.");
            logger::info("\"Staff experience ignores enchantment cost\" patch is NOT enabled... skipping.");
        }
    };

    bool StaffExp::EnchantmentGetSkillData(RE::EnchantmentItem* enchant, RE::MagicItem::SkillUsageData& skillUsage){
        return (enchant->GetSpellType() == RE::MagicSystem::SpellType::kStaffEnchantment ? StaffExp::StaffEnchantmentGetSkillData(enchant, skillUsage) : StaffExp::originalEnchantmentGetSkillData_(enchant, skillUsage));
    }

    bool StaffExp::StaffEnchantmentGetSkillData(RE::EnchantmentItem* enchant, RE::MagicItem::SkillUsageData& skillUsage){
        bool resetAutoCalcFlag = false;
        if (settings.staffExperienceIgnoresEnchantmentCost && !enchant->IsAutoCalc())
        {
            resetAutoCalcFlag = true;
            enchant->GetData()->flags ^= 1;
        }
        bool retVal = spellItemGetSkillData_(enchant, skillUsage);
        if (resetAutoCalcFlag)
        {
            enchant->GetData()->flags ^= 1;
        }
        return retVal;
    }

    REL::Relocation<decltype(StaffExp::EnchantmentGetSkillData)> StaffExp::originalEnchantmentGetSkillData_{};
    decltype(StaffExp::EnchantmentGetSkillData)* StaffExp::spellItemGetSkillData_{nullptr};
} // namespace Patch