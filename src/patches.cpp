#include "patches.h"
#include "dataHandler.h"

void scrollExpPatch::InstallPatch() {
	if(settings.scrollsGrantExperience)
	{
        // Replace ScrollItem::GetSkillUsageData with SpellItem::GetSkillUsageData
        REL::Relocation<uintptr_t> scrollPatch{ REL::ID(228867) }; // ScrollItem::VirtualFunctionTable, index 60 contains GetSkillUsageData
        REL::Relocation<uintptr_t> spellItemPatch{ REL::ID(228888) }; // SpellItem::VirtualFunctionTable, index 60 contains GetSkillUsageData
        REL::safe_write(reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(scrollPatch.address())[0x60])), reinterpret_cast<std::uintptr_t*>(spellItemPatch.address())[0x60]);
        logger::info("\"Scrolls grant experience\" patch installed!");
	}
    else
    {
        logger::info("\"Scrolls grant experience\" patch is NOT enabled... skipping.");
    }
};

void reflectDamagePatch::InstallPatch() {
	if(settings.reflectDamageLimitRemoval)
	{
        REL::Relocation<uintptr_t> patch{ REL::ID(42842) };
        SKSE::AllocTrampoline(1 << 4);
        REL::safe_write(patch.address() + 0x761, REL::NOP8, 8);
        logger::info("\"Reflect damage limit removal\" patch installed!");
	}
    else
    {
        logger::info("\"Reflect damage limit removal\" patch is NOT enabled... skipping.");
    }
};