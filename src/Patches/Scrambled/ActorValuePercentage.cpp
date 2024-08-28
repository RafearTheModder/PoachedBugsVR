/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "ActorValuePercentage.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
    void ActorValuePercentage::InstallPatch() {
        if(settings.actorValuePercentage)
        {
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::ActorValuePercentage::GetActorValuePercentage.address(), GetActorValuePercentage);

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::ActorValuePercentage::GetHealthPercentage.address(), GetHealthPercentage);

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::ActorValuePercentage::GetStaminaPercentage.address(), GetStaminaPercentage);

            logger::info("\"ActorValuePercentage\" patch installed!");
        }
        else
        {
            logger::info("\"ActorValuePercentage\" patch is NOT enabled... skipping.");
        }
    };
    
    float ActorValuePercentage::GetActorValuePercentage(RE::Actor* actor, RE::ActorValue actorValue)
    {
		auto permanentValue = actor->GetPermanentActorValue(actorValue);
		auto temporaryValue = actor->GetActorValueModifier(RE::ACTOR_VALUE_MODIFIER::kTemporary, actorValue);

		if (permanentValue + temporaryValue == 0.0F)
		{
			return 1.0F;
		}

		auto value = actor->GetActorValue(actorValue);

		return value / (permanentValue + temporaryValue);
    };

    float ActorValuePercentage::GetHealthPercentage(RE::Actor* actor)
    {
		return ActorValuePercentage::GetActorValuePercentage(actor, RE::ActorValue::kHealth);
    };

    float ActorValuePercentage::GetStaminaPercentage(RE::Actor* actor)
    {
		RE::NiPointer<RE::Actor> controllingActor;
		actor->GetControllingActor(controllingActor);

		return ActorValuePercentage::GetActorValuePercentage(controllingActor.get(), RE::ActorValue::kStamina);
    };
} // namespace Patch