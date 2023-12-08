#include "PerkEntrySpellCasterCorrection.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
    void PerkEntrySpellCasterCorrection::InstallPatch() {
        if(settings.perkEntrySpellCasterFix)
        {
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            // Bashing
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(RE::Address::PerkEntry::ApplySpell::ApplyBashingSpell.address(), ApplySpell);

            // CombatHit
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(RE::Address::PerkEntry::ApplySpell::ApplyCombatHitSpell.address(), ApplySpell);

            // ArrowHit
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(RE::Address::PerkEntry::ApplySpell::ApplyCombatHitArrowProjectileSpell.address(), ApplySpell);

            // Reanimate
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(RE::Address::PerkEntry::ApplySpell::ApplyReanimateSpell.address(), ApplySpell);

            // WeaponSwing
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(RE::Address::PerkEntry::ApplySpell::ApplyWeaponSwingSpell.address(), ApplySpell);

            logger::info("\"PerkEntrySpellCasterCorrection\" patch installed!");
        }
        else
        {
            logger::info("\"PerkEntrySpellCasterCorrection\" patch is NOT enabled... skipping.");
        }
    };

    void PerkEntrySpellCasterCorrection::ApplySpell(RE::Actor* target, RE::SpellItem* spell, RE::Actor* caster)
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
} // namespace Patch