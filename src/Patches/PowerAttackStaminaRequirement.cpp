#include "PowerAttackStaminaRequirement.h"

namespace Patch
{
    void PowerAttackStaminaRequirement::InstallPatch() {
        if(settings.powerAttacksStaminaRequirement)
        {
            logger::info("\"PowerAttackStaminaRequirement\" patch installed!");
        }
        else
        {
            logger::info("\"PowerAttackStaminaRequirement\" patch is NOT enabled... skipping.");
        }
    };
    
    float PowerAttackStaminaRequirement::ActorHasStamina(RE::ActorValueOwner* actorValueOwner, RE::BGSAttackData* attackData){

        return 0.0;
    };
    
    float PowerAttackStaminaRequirement::PlayerHasStamina(RE::ActorValueOwner* actorValueOwner, RE::BGSAttackData* attackData){

        return 0.0;
    };

    REL::Relocation<decltype(PowerAttackStaminaRequirement::ActorHasStamina)> PowerAttackStaminaRequirement::originalActorHasStamina_{};
    REL::Relocation<decltype(PowerAttackStaminaRequirement::ActorHasStamina)> PowerAttackStaminaRequirement::originalPlayerHasStamina_{};
} // namespace Patch