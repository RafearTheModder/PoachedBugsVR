/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "WeaponCharge.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
    void WeaponCharge::InstallPatch() {
        if(settings.weaponCharge)
        {
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::WeaponCharge::UpdateEquippedEnchantmentCharge.address(), UpdateEquippedEnchantmentCharge);

            logger::info("\"weaponCharge\" patch installed!");
        }
        else
        {
            logger::info("\"weaponCharge\" patch is NOT enabled... skipping.");
        }
    };
    
	void WeaponCharge::UpdateEquippedEnchantmentCharge(RE::Actor* actor, RE::TESForm* item, RE::ExtraDataList* extraDataList, bool leftHand)
	{
		if (!item)
		{
			return;
		}

		auto* player = RE::PlayerCharacter::GetSingleton();

		if (actor == player)
		{
			player->ResetInsufficientWeaponChargeMessage(leftHand);
		}

		auto* enchantment = item->GetEnchantment(extraDataList);

		if (!enchantment)
		{
			return;
		}

		if (enchantment->GetCastingType() == RE::MagicSystem::CastingType::kConstantEffect)
		{
			return;
		}

		auto castingSource  = leftHand ? RE::MagicSystem::CastingSource::kLeftHand : RE::MagicSystem::CastingSource::kRightHand;
		auto costActorValue = enchantment->GetCostActorValue(castingSource);

		if (costActorValue != RE::ActorValue::kNone)
		{
			actor->RemoveActorValueModifiers(costActorValue);

			auto maximumCharge = item->GetMaximumCharge(extraDataList);
			actor->SetActorValue(costActorValue, maximumCharge);

			if (extraDataList && extraDataList->HasType(RE::ExtraDataType::kCharge))
			{
				auto chargeData = extraDataList->GetByType<RE::ExtraCharge>();
				auto charge = chargeData ? chargeData->charge : -1.0F;
				actor->RestoreActorValue(RE::ACTOR_VALUE_MODIFIERS::kDamage, costActorValue, -(maximumCharge - charge));
			}
		}

		actor->SetSelectedSpell(castingSource, enchantment);
	};
} // namespace Patch