#include "PerkEntryMultipleSpellsApplication.h"

namespace Patch
{
    void PerkEntryMultipleSpellsApplication::InstallPatch() {
        if(settings.perkEntryMultipleSpellsApplication)
        {
            logger::info("\"PerkEntryMultipleSpellsApplication\" patch installed!");
        }
        else
        {
            logger::info("\"PerkEntryMultipleSpellsApplication\" patch is NOT enabled... skipping.");
        }
    };

    void PerkEntryMultipleSpellsApplication::AppendSpell(RE::Actor* perkedActor, std::uint32_t resultTypeEnum, std::uint8_t resultCount, void** results, RE::BGSEntryPointFunctionData* entryPointFunctionData)
    {

    };

    void PerkEntryMultipleSpellsApplication::ApplyAllBashingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells)
    {

    };

    void PerkEntryMultipleSpellsApplication::ApplyAllCombatHitSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells)
    {

    };

    void PerkEntryMultipleSpellsApplication::ApplyAllCombatHitArrowProjectileSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells)
    {

    };

    void PerkEntryMultipleSpellsApplication::ApplyAllReanimateSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells)
    {

    };

    void PerkEntryMultipleSpellsApplication::ApplyAllSneakingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells)
    {

    };

    void PerkEntryMultipleSpellsApplication::ApplyAllWeaponSwingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells)
    {

    };

	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllBashingSpells)>                  PerkEntryMultipleSpellsApplication::originalApplyAllBashingSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllCombatHitSpells)>                PerkEntryMultipleSpellsApplication::originalApplyAllCombatHitSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllCombatHitArrowProjectileSpells)> PerkEntryMultipleSpellsApplication::originalApplyAllCombatHitArrowProjectileSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllReanimateSpells)>                PerkEntryMultipleSpellsApplication::originalApplyAllReanimateSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllSneakingSpells)>                 PerkEntryMultipleSpellsApplication::originalApplyAllSneakingSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllWeaponSwingSpells)>              PerkEntryMultipleSpellsApplication::originalApplyAllWeaponSwingSpells;
} // namespace Patch