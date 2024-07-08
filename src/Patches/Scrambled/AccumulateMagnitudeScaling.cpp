/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "AccumulateMagnitudeScaling.h"

#include "Addresses.h"

namespace Patch
{
    void AccumulateMagnitudeScaling::InstallPatch() {
        if(settings.accumulateMagnitudeScaling)
        {
            originalInstantiateFunction_ =
                reinterpret_cast<decltype(AccumulateMagnitudeScaling::originalInstantiateFunction_)*>(RE::Address::ActiveEffectFactory::InstantiateFunctions.address())
                    [std::to_underlying(RE::EffectArchetypes::ArchetypeID::kAccumulateMagnitude)];

            reinterpret_cast<decltype(AccumulateMagnitudeScaling::InstantiateFunction)**>(RE::Address::ActiveEffectFactory::InstantiateFunctions.address())
                [std::to_underlying(RE::EffectArchetypes::ArchetypeID::kAccumulateMagnitude)] = std::addressof(AccumulateMagnitudeScaling::InstantiateFunction);

            auto functionCallOperatorPtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(
                                                RE::VTABLE_FindMaxMagnitudeVisitor[0].address())[0x1]));
            REL::safe_write(functionCallOperatorPtr, reinterpret_cast<std::uintptr_t>(std::addressof(AccumulateMagnitudeScaling::FunctionCallOperator)));

            auto updateActorValuePtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(
                                                RE::VTABLE_AccumulatingValueModifierEffect[0].address())[0x1D]));
            REL::safe_write(updateActorValuePtr, reinterpret_cast<std::uintptr_t>(std::addressof(AccumulateMagnitudeScaling::UpdateActorValue)));
            logger::info("\"accumulateMagnitudeScaling\" patch installed!");
        }
        else
        {
            logger::info("\"accumulateMagnitudeScaling\" patch is NOT enabled... skipping.");
        }
    };

    float AccumulateMagnitudeScaling::FindMaximumPower(RE::MagicTarget* magicTarget, RE::ActiveEffect* activeEffect)
    {
		RE::FindMaxMagnitudeVisitor findMaxMagnitudeVisitor;

		findMaxMagnitudeVisitor.activeEffect = activeEffect;
		findMaxMagnitudeVisitor.maxMagnitude     = -1.0F;

		magicTarget->ForEachActiveEffect(findMaxMagnitudeVisitor);

		return findMaxMagnitudeVisitor.maxMagnitude;
    };

    RE::BSContainer::ForEachResult AccumulateMagnitudeScaling::FunctionCallOperator(RE::FindMaxMagnitudeVisitor* findMaxMagnitudeVisitor, RE::ActiveEffect* activeEffect)
    {

		auto* accumulatingValueModifierEffect = static_cast<RE::AccumulatingValueModifierEffect*>(activeEffect);
		if ((!activeEffect) ||
            (activeEffect == findMaxMagnitudeVisitor->activeEffect) ||
            (activeEffect->GetBaseObject()->GetArchetype() != RE::EffectArchetypes::ArchetypeID::kAccumulateMagnitude)||
            (accumulatingValueModifierEffect->actorValue != RE::ActorValue::kWardPower))
		{
			return RE::BSContainer::ForEachResult::kContinue;
		}

		auto accumulationRate = accumulatingValueModifierEffect->GetMagnitude();

		if (accumulationRate > findMaxMagnitudeVisitor->maxMagnitude)
		{
			findMaxMagnitudeVisitor->maxMagnitude = accumulationRate;
		}

		return RE::BSContainer::ForEachResult::kContinue;
    };

    RE::AccumulatingValueModifierEffect* AccumulateMagnitudeScaling::InstantiateFunction(RE::Actor* caster, RE::MagicItem* magicItem, RE::Effect* effect)
    {
        auto accumulatingValueModifierEffect = originalInstantiateFunction_(caster, magicItem, effect);

        std::swap(accumulatingValueModifierEffect->magnitude, accumulatingValueModifierEffect->maximumMagnitude);

        return accumulatingValueModifierEffect;
    };

    void AccumulateMagnitudeScaling::UpdateActorValue(RE::AccumulatingValueModifierEffect* accumulatingValueModifierEffect, float frameTime)
    {
        if (accumulatingValueModifierEffect->holdTimer <= 0.0)
        {
            auto* targetActor = accumulatingValueModifierEffect->GetTargetActor();

            if (targetActor)
            {
                // Swap accumulation rate and the maximum magnitude
                auto maxMagnitude = accumulatingValueModifierEffect->GetMagnitude();
                auto accumulationRate = accumulatingValueModifierEffect->maximumMagnitude * frameTime;

                if (accumulatingValueModifierEffect->actorValue == RE::ActorValue::kWardPower)
                {
                    /* Update maximum ward power */
                    auto maxWardPower = AccumulateMagnitudeScaling::FindMaximumPower(targetActor, nullptr);
                    targetActor->currentProcess->middleHigh->maximumWardPower = maxWardPower;

                    if (maxWardPower > 0.0F)
                    {
                        maxMagnitude = maxWardPower;
                    }
                }

                auto currentMagnitude = targetActor->GetActorValue(accumulatingValueModifierEffect->actorValue);

                if (currentMagnitude + accumulationRate > maxMagnitude)
                {
                    accumulationRate = maxMagnitude - currentMagnitude;
                }

                accumulatingValueModifierEffect->ModifyActorValue(targetActor, accumulationRate, RE::ActorValue::kNone);
                accumulatingValueModifierEffect->accumulatedMagnitude += accumulationRate;
            }
        }
		else
		{
			accumulatingValueModifierEffect->holdTimer -= frameTime;
		}
    };

    REL::Relocation<decltype(AccumulateMagnitudeScaling::InstantiateFunction)> AccumulateMagnitudeScaling::originalInstantiateFunction_{};
} // namespace Patch