#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class PerkEntryMultipleSpellsApplication
    {
    public:
        static void InstallPatch();
    private:
        static void AppendSpell(RE::Actor* perkedActor, std::uint32_t resultTypeEnum, std::uint8_t resultCount, void** results, RE::BGSEntryPointFunctionData* entryPointFunctionData);

        static void ApplyAllBashingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells);
        static void ApplyAllCombatHitSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::TESObjectWEAP* weapon, RE::Actor* target, RE::SpellItem** spells);
        static void ApplyAllCombatHitArrowProjectileSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::TESObjectWEAP* weapon, RE::Actor* target, RE::SpellItem** spells);
        static void ApplyAllReanimateSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::SpellItem* spell, RE::Actor* target, RE::SpellItem** spells);
        static void ApplyAllSneakingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::SpellItem** spells);
        static void ApplyAllWeaponSwingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::TESObjectWEAP* weapon, RE::SpellItem** spells);

		static REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllBashingSpells)>                  originalApplyAllBashingSpells;
		static REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllCombatHitSpells)>                originalApplyAllCombatHitSpells;
		static REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllCombatHitArrowProjectileSpells)> originalApplyAllCombatHitArrowProjectileSpells;
		static REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllReanimateSpells)>                originalApplyAllReanimateSpells;
		static REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllSneakingSpells)>                 originalApplyAllSneakingSpells;
		static REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllWeaponSwingSpells)>              originalApplyAllWeaponSwingSpells;
    };
} // namespace Patch