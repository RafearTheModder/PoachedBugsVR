/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "ImproveAllEnchantmentEffects.h"
#include "Utilities/ExtraRE.h"

namespace Patch
{
    void ImproveAllEnchantmentEffects::InstallPatch() {
        if(settings.improveAllEnchantmentEffects)
        {
            REL::Relocation<uintptr_t> enchantmentItemVtable{ RE::VTABLE_CraftingSubMenus__EnchantConstructMenu__CreateEffectFunctor[0] }; // index 1 of this vtable has the functor we are looking for
            originalAddEffect_ = enchantmentItemVtable.write_vfunc(0x1, ImproveAllEnchantmentEffects::AddEffect);
            logger::info("\"ImproveAllEnchantmentEffects\" patch installed!");
        }
        else
        {
            logger::info("\"ImproveAllEnchantmentEffects\" patch is NOT enabled... skipping.");
        }
    };

    RE::BSContainer::ForEachResult ImproveAllEnchantmentEffects::AddEffect(RE::CraftingSubMenus::EnchantConstructMenu::CreateEffectFunctor* createEffectFunctor, RE::Effect* effect){
		auto createdEffectIndex = REX::BSTArrayAddElement(&createEffectFunctor->createdEffects, effect);

		auto magnitude = effect->GetMagnitude();
		auto duration  = effect->GetDuration();

		auto effectSettingFlags    = effect->baseEffect->data.flags;
		auto powerAffectsMagnitude = effectSettingFlags.all(RE::EffectSetting::EffectSettingData::Flag::kPowerAffectsMagnitude);
		auto powerAffectsDuration  = effectSettingFlags.all(RE::EffectSetting::EffectSettingData::Flag::kPowerAffectsDuration);

		float power{ 1.0F };

		auto enchantmentEntry = createEffectFunctor->enchantmentParams;

		if (enchantmentEntry)
		{
			float maximumPower{ 1.0F };

			if (powerAffectsMagnitude)
			{
				maximumPower = magnitude;
			}
			else if (powerAffectsDuration)
			{
				maximumPower = static_cast<float>(duration);
			}

			auto player          = RE::PlayerCharacter::GetSingleton();
			auto enchantingSkill = player->GetActorValue(RE::ActorValue::kEnchanting);

			maximumPower = RE::EnchantmentItem::ModifyPower(maximumPower, enchantingSkill);
			RE::BGSEntryPoint::HandleEntryPoint(RE::BGSEntryPoint::ENTRY_POINTS::kModEnchantmentPower, player, enchantmentEntry->data, createEffectFunctor->baseObject, std::addressof(maximumPower));
			maximumPower = std::floor(maximumPower);

			if (effect == createEffectFunctor->costliestEffect)
			{
				power = enchantmentEntry->magnitude;

				if (power > maximumPower)
				{
					power = maximumPower;
				}
				else if (power < 1.0F)
				{
					power = 1.0F;
				}

				if (maximumPower != enchantmentEntry->maxMagnitude)
				{
					power = maximumPower;
				}

				enchantmentEntry->maxMagnitude = maximumPower;

				if (enchantmentEntry->filterFlag.all(RE::CraftingSubMenus::EnchantConstructMenu::FilterFlag::EffectWeapon))
				{
					enchantmentEntry->magnitude = power;
				}
				else if (enchantmentEntry->filterFlag.all(RE::CraftingSubMenus::EnchantConstructMenu::FilterFlag::EffectArmor))
				{
					power = maximumPower * createEffectFunctor->soulGemRatio;

					if (power < 1.0F)
					{
						power = 1.0F;
					}

					enchantmentEntry->magnitude = power;
				}
			}
			else
			{
				power = maximumPower;

				if (enchantmentEntry->filterFlag.all(RE::CraftingSubMenus::EnchantConstructMenu::FilterFlag::EffectArmor))
				{
					power = maximumPower * createEffectFunctor->soulGemRatio;

					if (power < 1.0F)
					{
						power = 1.0F;
					}
				}
			}
		}

		if (powerAffectsMagnitude)
		{
			magnitude = power;
		}
		else if (powerAffectsDuration)
		{
			duration = static_cast<std::uint32_t>(std::round(power));
		}

		REX::SetEffectMagnitude(&createEffectFunctor->createdEffects[createdEffectIndex], magnitude);
		REX::SetEffectDuration(&createEffectFunctor->createdEffects[createdEffectIndex], duration);

		return RE::BSContainer::ForEachResult::kContinue;
    };

    REL::Relocation<decltype(ImproveAllEnchantmentEffects::AddEffect)> ImproveAllEnchantmentEffects::originalAddEffect_{};
} // namespace Patch