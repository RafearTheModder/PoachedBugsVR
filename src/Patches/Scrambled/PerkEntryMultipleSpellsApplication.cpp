/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "PerkEntryMultipleSpellsApplication.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
    void PerkEntryMultipleSpellsApplication::InstallPatch() {
        if(settings.perkEntryMultipleSpellsApplication)
        {
            *reinterpret_cast<decltype(&PerkEntryMultipleSpellsApplication::AppendSpell)*>(RE::Address::PerkEntry::SelectSpellFunctionPointer.address()) = std::addressof(PerkEntryMultipleSpellsApplication::AppendSpell);

            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            SKSE::AllocTrampoline(1 << 4);
            originalApplyAllBashingSpells = trampoline.write_call<5>(RE::Address::PerkEntry::HandlePerkEntry::SelectBashingSpell.address(), ApplyAllBashingSpells);

            SKSE::AllocTrampoline(1 << 4);
            originalApplyAllCombatHitSpells = trampoline.write_call<5>(RE::Address::PerkEntry::HandlePerkEntry::SelectCombatHitSpell.address(), ApplyAllCombatHitSpells);

            SKSE::AllocTrampoline(1 << 4);
            originalApplyAllCombatHitArrowProjectileSpells = trampoline.write_call<5>(RE::Address::PerkEntry::HandlePerkEntry::SelectCombatHitArrowProjectileSpell.address(), ApplyAllCombatHitArrowProjectileSpells);

            SKSE::AllocTrampoline(1 << 4);
            originalApplyAllReanimateSpells = trampoline.write_call<5>(RE::Address::PerkEntry::HandlePerkEntry::SelectReanimateSpell.address(), ApplyAllReanimateSpells);

            SKSE::AllocTrampoline(1 << 4);
            originalApplyAllSneakingSpells = trampoline.write_call<5>(RE::Address::PerkEntry::HandlePerkEntry::SelectSneakingSpell.address(), ApplyAllSneakingSpells);

            SKSE::AllocTrampoline(1 << 4);
            originalApplyAllWeaponSwingSpells = trampoline.write_call<5>(RE::Address::PerkEntry::HandlePerkEntry::SelectWeaponSwingSpell.address(), ApplyAllWeaponSwingSpells);

            logger::info("\"PerkEntryMultipleSpellsApplication\" patch installed!");
        }
        else
        {
            logger::info("\"PerkEntryMultipleSpellsApplication\" patch is NOT enabled... skipping.");
        }
    };

    void PerkEntryMultipleSpellsApplication::AppendSpell(RE::Actor* perkedActor, std::uint32_t resultTypeEnum, std::uint8_t resultCount, void** results, RE::BGSEntryPointFunctionData* entryPointFunctionData)
    {
        auto expectedResultCount = *reinterpret_cast<std::uint32_t*>(RE::Address::PerkEntry::SelectSpellFunctionResultCount.address());
        if ((resultCount != expectedResultCount)||
            (resultTypeEnum != 4)|| // 4 is spellItem return type, which is the only one we should act on in here.
            (entryPointFunctionData->GetType() != RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kSpellItem))
        {
            return;
        }

        RE::SpellItem* spell = static_cast<RE::BGSEntryPointFunctionDataSpellItem*>(entryPointFunctionData)->spell;
        if (spell)
        {
            auto* spells = static_cast<std::vector<RE::SpellItem*>*>(*results);
            spells->push_back(spell);
        }
    };

    // TODO: Refactor this out to a module for helper functions.
    void ApplySpellToTarget(RE::SpellItem* spell, RE::Actor* target, RE::Actor* caster)
    {
        switch (spell->GetSpellType())
        {
            case RE::MagicSystem::SpellType::kDisease:
            case RE::MagicSystem::SpellType::kAbility:
            case RE::MagicSystem::SpellType::kAddiction:
            {
                target->AddSpell(spell);
            }
            default:
            {
                caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(spell, false, target, 1.0F, false, 0.0F, nullptr);
            }
        }
    };

    void PerkEntryMultipleSpellsApplication::ApplyAllBashingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::SpellItem** spells)
    {
       std::vector<RE::SpellItem*> spellArray;

        originalApplyAllBashingSpells(entryPointEnum, perkedActor, target, reinterpret_cast<RE::SpellItem**>(std::addressof(spellArray)));

        for (RE::SpellItem* spell : spellArray)
        {
            ApplySpellToTarget(spell, target, settings.perkEntrySpellCasterFix ? perkedActor : target);
        }
    };

    void PerkEntryMultipleSpellsApplication::ApplyAllCombatHitSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::TESObjectWEAP* weapon, RE::Actor* target, RE::SpellItem** spells)
    {
       std::vector<RE::SpellItem*> spellArray;

        originalApplyAllCombatHitSpells(entryPointEnum, perkedActor, weapon, target, reinterpret_cast<RE::SpellItem**>(std::addressof(spellArray)));

        for (RE::SpellItem* spell : spellArray)
        {
            ApplySpellToTarget(spell, target, settings.perkEntrySpellCasterFix ? perkedActor : target);
        }
    };

    void PerkEntryMultipleSpellsApplication::ApplyAllCombatHitArrowProjectileSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::TESObjectWEAP* weapon, RE::Actor* target, RE::SpellItem** spells)
    {
       std::vector<RE::SpellItem*> spellArray;

        originalApplyAllCombatHitArrowProjectileSpells(entryPointEnum, perkedActor, weapon, target, reinterpret_cast<RE::SpellItem**>(std::addressof(spellArray)));

        for (RE::SpellItem* spell : spellArray)
        {
            ApplySpellToTarget(spell, target, settings.perkEntrySpellCasterFix ? perkedActor : target);
        }
    };

    void PerkEntryMultipleSpellsApplication::ApplyAllReanimateSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::SpellItem* spell, RE::Actor* target, RE::SpellItem** spells)
    {
       std::vector<RE::SpellItem*> spellArray;

        originalApplyAllReanimateSpells(entryPointEnum, perkedActor, spell, target, reinterpret_cast<RE::SpellItem**>(std::addressof(spellArray)));

        for (RE::SpellItem* spell : spellArray)
        {
            ApplySpellToTarget(spell, target, settings.perkEntrySpellCasterFix ? perkedActor : target);
        }
    };

    void PerkEntryMultipleSpellsApplication::ApplyAllSneakingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::SpellItem** spells)
    {
       std::vector<RE::SpellItem*> spellArray;

        originalApplyAllSneakingSpells(entryPointEnum, perkedActor, reinterpret_cast<RE::SpellItem**>(std::addressof(spellArray)));

        for (RE::SpellItem* spell : spellArray)
        {
            ApplySpellToTarget(spell, perkedActor, perkedActor);
        }
    };

    void PerkEntryMultipleSpellsApplication::ApplyAllWeaponSwingSpells(std::uint32_t entryPointEnum, RE::Actor* perkedActor, RE::Actor* target, RE::TESObjectWEAP* weapon, RE::SpellItem** spells)
    {
       std::vector<RE::SpellItem*> spellArray;

        originalApplyAllWeaponSwingSpells(entryPointEnum, perkedActor, target, weapon, reinterpret_cast<RE::SpellItem**>(std::addressof(spellArray)));

        for (RE::SpellItem* spell : spellArray)
        {
            ApplySpellToTarget(spell, target, settings.perkEntrySpellCasterFix ? perkedActor : target);
        }
    };

	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllBashingSpells)>                  PerkEntryMultipleSpellsApplication::originalApplyAllBashingSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllCombatHitSpells)>                PerkEntryMultipleSpellsApplication::originalApplyAllCombatHitSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllCombatHitArrowProjectileSpells)> PerkEntryMultipleSpellsApplication::originalApplyAllCombatHitArrowProjectileSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllReanimateSpells)>                PerkEntryMultipleSpellsApplication::originalApplyAllReanimateSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllSneakingSpells)>                 PerkEntryMultipleSpellsApplication::originalApplyAllSneakingSpells;
	REL::Relocation<decltype(PerkEntryMultipleSpellsApplication::ApplyAllWeaponSwingSpells)>              PerkEntryMultipleSpellsApplication::originalApplyAllWeaponSwingSpells;
} // namespace Patch