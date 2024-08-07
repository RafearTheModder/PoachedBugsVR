/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class AccumulateMagnitudeScaling
    {
    public:
        static void InstallPatch();
    private:
        static float FindMaximumPower(RE::MagicTarget* magicTarget, RE::ActiveEffect* activeEffect);
        static RE::BSContainer::ForEachResult FunctionCallOperator(RE::FindMaxMagnitudeVisitor* findMaxMagnitudeVisitor, RE::ActiveEffect* activeEffect);
        static RE::AccumulatingValueModifierEffect* InstantiateFunction(RE::Actor* caster, RE::MagicItem* magicItem, RE::Effect* effect);
		static void UpdateActorValue(RE::AccumulatingValueModifierEffect* accumulatingValueModifierEffect, float frameTime);

        static REL::Relocation<decltype(AccumulateMagnitudeScaling::InstantiateFunction)> originalInstantiateFunction_;
    };
} // namespace Patch