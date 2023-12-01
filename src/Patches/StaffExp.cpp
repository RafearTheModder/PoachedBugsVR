#include "StaffExp.h"

namespace Patch
{
    void StaffExp::InstallPatch() {
        if(settings.stavesGrantExperience)
        {
            REL::Relocation<uintptr_t> enchantmentItemVtable{ RE::VTABLE_EnchantmentItem[0] }; // EnchantmentItem::VirtualFunctionTable, index 0x60 contains GetSkillUsageData
            originalEnchantmentGetSkillData_ = reinterpret_cast<decltype(StaffExp::originalEnchantmentGetSkillData_)>(std::addressof(reinterpret_cast<std::uintptr_t*>(enchantmentItemVtable.address())[0x60]));
            REL::safe_write(reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(enchantmentItemVtable.address())[0x60])), reinterpret_cast<std::uintptr_t>(StaffExp::EnchantmentGetSkillData));
            logger::info("\"Staves grant experience\" patch installed!");
        }
        else
        {
            logger::info("\"Staves grant experience\" patch is NOT enabled... skipping.");
        }
    };

    bool StaffExp::EnchantmentGetSkillData(RE::EnchantmentItem* enchant, RE::MagicItem::SkillUsageData& skillUsage){
        return (enchant->GetSpellType() == RE::MagicSystem::SpellType::kStaffEnchantment ? StaffExp::StaffEnchantmentGetSkillData(enchant, skillUsage) : StaffExp::originalEnchantmentGetSkillData_(enchant, skillUsage));
    }

    bool StaffExp::StaffEnchantmentGetSkillData(RE::EnchantmentItem* enchant, RE::MagicItem::SkillUsageData& skillUsage){
        return false;
    }

    decltype(StaffExp::EnchantmentGetSkillData)* StaffExp::originalEnchantmentGetSkillData_{nullptr};
} // namespace Patch