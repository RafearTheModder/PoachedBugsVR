#pragma once

#include "REL/Relocation.h"

namespace RE
{
	namespace Address
	{
        inline const REL::Relocation<std::uintptr_t> OnFrameUpdate(REL::ID(35565).address() + 0x33);

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

        namespace HarvestedFlags
        {
            // Awaiting addition to address library
            inline const REL::Relocation<std::uintptr_t> SetEmpty{REL::ID(18843).address() + 0x31c};
        }

        namespace LeveledCharacters
        {
            inline const REL::Relocation<std::uintptr_t> GetAllBelowForce{REL::ID(12448).address()};
        }

        namespace WeaponCharge
        {
            inline const REL::Relocation<std::uintptr_t> UpdateEquippedEnchantmentCharge{REL::ID(37803).address()};
        }

        namespace Actor
        {
            inline const REL::Relocation<std::uintptr_t> AdjustHealthDamageToDifficulty{REL::ID(36506).address()};
        }

		namespace EnchantmentCost
		{
            inline const REL::Relocation<std::uintptr_t> Compare{REL::ID(35284).address() + 0x72};
		}

        namespace ActorValuePercentage
        {
            inline const REL::Relocation<std::uintptr_t> GetActorValuePercentage{REL::ID(36347).address()};
            inline const REL::Relocation<std::uintptr_t> GetHealthPercentage{REL::ID(36349).address()};
            inline const REL::Relocation<std::uintptr_t> GetStaminaPercentage{REL::ID(36348).address()};
        }

		namespace ArmorWeightModPerkEntry
		{
            inline const REL::Relocation<std::uintptr_t> GetInventoryWeight{REL::ID(15883).address()};
		}

        namespace TrainingMenu
        {
            inline const REL::Relocation<std::uintptr_t> GetPermanentActorValue{REL::ID(51794).address() + 0x28c};
        }
	}
}