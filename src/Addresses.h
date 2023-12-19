#pragma once

#include "REL/Relocation.h"

namespace RE
{
	namespace Address
	{
        namespace ReflectDamage
        {
            inline const REL::Relocation<std::uintptr_t> CompareReflectDamageAV{REL::ID(42842).address() + 0x761};
        }

        namespace PerkEntry
        {
            inline const REL::Relocation<REL::ID> SelectSpellFunctionPointer{REL::ID(675819)};
            inline const REL::Relocation<REL::ID> SelectSpellFunctionResultCount{REL::ID(502190)};

            namespace HandlePerkEntry
            {
                inline const REL::Relocation<std::uintptr_t> SelectBashingSpell{REL::ID(37673).address() + 0x40E};
                inline const REL::Relocation<std::uintptr_t> SelectCombatHitSpell{REL::ID(37799).address() + 0x61};
                inline const REL::Relocation<std::uintptr_t> SelectCombatHitArrowProjectileSpell{REL::ID(42547).address() + 0x28B};
                inline const REL::Relocation<std::uintptr_t> SelectReanimateSpell{REL::ID(37865).address() + 0xBA};
                inline const REL::Relocation<std::uintptr_t> SelectSneakingSpell{REL::ID(36926).address() + 0xB6};
                inline const REL::Relocation<std::uintptr_t> SelectWeaponSwingSpell{REL::ID(37628).address() + 0xAB};
            }
            
            namespace ApplySpell
            {
                inline const REL::Relocation<std::uintptr_t> ApplyBashingSpell{REL::ID(37673).address() + 0x429};
                inline const REL::Relocation<std::uintptr_t> ApplyCombatHitSpell{REL::ID(37799).address() + 0x79};
                inline const REL::Relocation<std::uintptr_t> ApplyCombatHitArrowProjectileSpell{REL::ID(42547).address() + 0x2A7};
                inline const REL::Relocation<std::uintptr_t> ApplyReanimateSpell{REL::ID(37865).address() + 0xD2};
                inline const REL::Relocation<std::uintptr_t> ApplyWeaponSwingSpell{REL::ID(37628).address() + 0xC3};
            }
        }

        namespace PowerAttackStaminaChecks
        {
            inline const REL::Relocation<std::uintptr_t> GetActorAttackStamina{REL::ID(48139).address() + 0x29B};
            inline const REL::Relocation<std::uintptr_t> ActorHasStamina{REL::ID(48139).address() + 0x293};

            inline const REL::Relocation<std::uintptr_t> GetPlayerAttackStamina{REL::ID(38047).address() + 0xBB};
            inline const REL::Relocation<std::uintptr_t> PlayerHasStamina{REL::ID(38047).address() + 0xE1};
        }
        
        namespace ActiveEffectFactory
        {
            inline const REL::Relocation<REL::ID> InstantiateFunctions{REL::ID(516691)};
        }
	}
}