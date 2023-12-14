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

    };

    // RE::BSContainer::ForEachResult AccumulateMagnitudeScaling::FunctionCallOperator(RE::FindMaxMagnitudeVisitor* findMaxMagnitudeVisitor, RE::ActiveEffect* activeEffect);
    RE::BSContainer::ForEachResult AccumulateMagnitudeScaling::FunctionCallOperator(void* findMaxMagnitudeVisitor, RE::ActiveEffect* activeEffect) // Replace with above line when RE is done on FindMaxMagnitudeVisitor
    {
        return RE::BSContainer::ForEachResult::kStop;
    };

    RE::AccumulatingValueModifierEffect* AccumulateMagnitudeScaling::InstantiateFunction(RE::Actor* caster, RE::MagicItem* magicItem, RE::Effect* effect)
    {
        auto accumulatingValueModifierEffect = originalInstantiateFunction_(caster, magicItem, effect);

        std::swap(accumulatingValueModifierEffect->magnitude, accumulatingValueModifierEffect->maximumMagnitude);

        return accumulatingValueModifierEffect;
    };

    void AccumulateMagnitudeScaling::UpdateActorValue(RE::AccumulatingValueModifierEffect* accumulatingValueModifierEffect, float frameTime)
    {

    };

    REL::Relocation<decltype(AccumulateMagnitudeScaling::InstantiateFunction)> AccumulateMagnitudeScaling::originalInstantiateFunction_{};
} // namespace Patch