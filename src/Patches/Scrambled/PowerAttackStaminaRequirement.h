/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class PowerAttackStaminaRequirement
    {
    public:
        static void InstallPatch();
    private:
        static float ActorHasStamina(RE::ActorValueOwner* actorValueOwner, RE::BGSAttackData* attackData);
        static float PlayerHasStamina(RE::ActorValueOwner* actorValueOwner, RE::BGSAttackData* attackData);
    
        static REL::Relocation<decltype(PowerAttackStaminaRequirement::ActorHasStamina)> originalActorHasStamina_;
        static REL::Relocation<decltype(PowerAttackStaminaRequirement::ActorHasStamina)> originalPlayerHasStamina_;
    };
} // namespace Patch