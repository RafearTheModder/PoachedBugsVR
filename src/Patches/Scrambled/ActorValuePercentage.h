/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class ActorValuePercentage
    {
    public:
        static void InstallPatch();

    private:
		static float GetActorValuePercentage(RE::Actor* actor, RE::ActorValue actorValue);
		static float GetHealthPercentage(RE::Actor* actor);
		static float GetStaminaPercentage(RE::Actor* actor);
    };
} // namespace Patch