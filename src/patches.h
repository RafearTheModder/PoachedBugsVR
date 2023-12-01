#pragma once
#include "RE/Skyrim.h"

/*DONE*/
class scrollExpPatch
{
public:
    static void InstallPatch() {
        // Replace ScrollItem::GetSkillUsageData with SpellItem::GetSkillUsageData
        REL::Relocation<uintptr_t> scrollPatch{ REL::ID(228867) };
        REL::Relocation<uintptr_t> spellItemPatch{ REL::ID(228888) };
        REL::safe_write(reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(scrollPatch.address())[0x60])), reinterpret_cast<std::uintptr_t*>(spellItemPatch.address())[0x60]);
		logger::info("Scroll Experience patch installed!");
    };
private:
};

/*DOING*/
class reflectDamagePatch
{
public:
    static void InstallPatch() {
        // TODO: Revisit address and offset. Address maps, but offset seems to be wrong as evidenced by damage reflection still being capped.
        REL::Relocation<uintptr_t> patch{ REL::ID(42842) };
        SKSE::AllocTrampoline(1 << 4);
        REL::safe_write(patch.address() + 0x544, REL::NOP8, 8);
		logger::info("Reflect Damage patch installed!");
    };
private:
};
