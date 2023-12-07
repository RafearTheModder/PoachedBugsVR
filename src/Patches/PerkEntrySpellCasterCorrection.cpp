#include "PerkEntrySpellCasterCorrection.h"
#include "SKSE/Trampoline.h"

namespace Patch
{
    void PerkEntrySpellCasterCorrection::InstallPatch() {
        if(settings.perkEntrySpellCasterFix)
        {
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            // Bashing
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(REL::ID(37673).address() + 0x429, ApplySpell);

            // CombatHit
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(REL::ID(37799).address() + 0x79, ApplySpell);

            // ArrowHit
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(REL::ID(42547).address() + 0x2A7, ApplySpell);

            // Reanimate
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(REL::ID(37865).address() + 0xD2, ApplySpell);

            // WeaponSwing
            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(REL::ID(37628).address() + 0xC3, ApplySpell);

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