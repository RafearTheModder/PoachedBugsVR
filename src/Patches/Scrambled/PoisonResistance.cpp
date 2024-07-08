/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "PoisonResistance.h"

namespace Patch
{
    void PoisonResistance::InstallPatch() {
        if(settings.poisonsUseOtherResistances)
        {
            auto actorCheckResistanceFuncPtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(RE::VTABLE_Actor[4].address())[0xA]));
            REL::safe_write(actorCheckResistanceFuncPtr, reinterpret_cast<std::uintptr_t>(std::addressof(PoisonResistance::CheckResistance)));

            auto characterCheckResistanceFuncPtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(RE::VTABLE_Character[4].address())[0xA]));
            REL::safe_write(characterCheckResistanceFuncPtr, reinterpret_cast<std::uintptr_t>(std::addressof(PoisonResistance::CheckResistance)));

            auto playerCheckResistanceFuncPtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(RE::VTABLE_PlayerCharacter[4].address())[0xA]));
            REL::safe_write(playerCheckResistanceFuncPtr, reinterpret_cast<std::uintptr_t>(std::addressof(PoisonResistance::CheckResistance)));

            logger::info("\"Poisons use other resistances\" patch installed!");
        }
        else
        {
            logger::info("\"Poisons use other resistances\" patch is NOT enabled... skipping.");
        }
    };
    
    float PoisonResistance::CheckResistance(RE::MagicTarget* a_magicTarget, RE::MagicItem* a_magicItem, RE::Effect* a_effect, RE::TESBoundObject* a_object){
        if (a_magicItem->hostileCount <=0 || (a_object && a_object->formType == RE::FormType::Armor))
        {
            return 1.0;
        }

        auto type = a_magicItem->GetSpellType();
        RE::AlchemyItem* potion{nullptr};
        if (type == RE::MagicSystem::SpellType::kPotion)
        {
            potion = static_cast<RE::AlchemyItem*>(a_magicItem);
        }
        bool isPoison = false;
        if (potion)
        {
            isPoison = potion->IsPoison();
        }
        
        if ((potion && !isPoison && !a_effect->IsHostile())||\
            (type == RE::MagicSystem::SpellType::kIngredient && a_magicItem->IsFood()))
        {
            return 1.0;
        }

        auto* a_magicTargetAsActor = static_cast<RE::Actor*>(a_magicTarget);
        float magicResistance = a_magicTargetAsActor->GetActorValue(RE::ActorValue::kResistMagic);;
        float specificResistance{0.0};
        auto actorValueForResistance = a_effect->baseEffect->data.resistVariable;

        if (actorValueForResistance != RE::ActorValue::kNone)
        {
            specificResistance = a_magicTargetAsActor->GetActorValue(actorValueForResistance);
        }
        
        if (a_magicTargetAsActor == RE::PlayerCharacter::GetSingleton())
        {
            float maxResistanceValue = RE::GameSettingCollection::GetSingleton()->GetSetting("fPlayerMaxResistance")->GetFloat();
            magicResistance = (magicResistance >= maxResistanceValue ? maxResistanceValue : magicResistance);
            specificResistance = (specificResistance >= maxResistanceValue ? maxResistanceValue : specificResistance);
        }

        float finalDamageMult = (specificResistance >= 100.0 ? 0.0 : (1.0 - (specificResistance/100.0)));

        if (!(isPoison || type == RE::MagicSystem::SpellType::kPoison))
        {
            finalDamageMult *= (magicResistance >= 100.0 ? 0.0 : (1.0 - (magicResistance/100.0)));
        }

        return finalDamageMult;
    };
} // namespace Patch