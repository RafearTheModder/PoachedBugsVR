#include "MagicEffectPotencyFlags.h"

#include "Addresses.h"

namespace Patch
{
    /*TODO: Implement MagicEffectPotencyFlags
            This patch will force the game to actually respect the "power affects magnitude/duration" and "no magnitude/duration" flags
            labels: Type:Feature, Status:Backlog, Priority:2*/
    void MagicEffectPotencyFlags::InstallPatch() {
        if(settings.magicEffectPotencyFlags)
        {
            // Need to write absolute jumps to Adjust and Restart as overrides to the base/vanilla functions here. 
            logger::info("\"MagicEffectPotencyFlags\" patch installed!");
        }
        else
        {
            logger::info("\"MagicEffectPotencyFlags\" patch is NOT enabled... skipping.");
        }
    };

    /*TODO: Move SpellShouldAdjustEffects to helper library
            This function may be helpful in other contexts
            labels: Type:Refactoring, Status:Backlog, Priority:3*/
    bool SpellShouldAdjustEffects(RE::MagicItem* theSpell){
        auto spellType = theSpell->GetSpellType();
        if ((spellType == RE::MagicSystem::SpellType::kDisease)||
            (spellType == RE::MagicSystem::SpellType::kAbility)||
            (spellType == RE::MagicSystem::SpellType::kIngredient)||
            (spellType == RE::MagicSystem::SpellType::kAddiction)||
            ((spellType == RE::MagicSystem::SpellType::kEnchantment) && (theSpell->GetCastingType() == RE::MagicSystem::CastingType::kConstantEffect)))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void MagicEffectPotencyFlags::Adjust(RE::ActiveEffect* activeEffect, float effectiveness, bool requireHostility){
        auto* spell = activeEffect->spell;

        if ((!SpellShouldAdjustEffects(spell))||
            (requireHostility && !activeEffect->effect->IsHostile())||
            (effectiveness == 1.0)||
            (effectiveness < 0.0))
        {
            return;
        }
        
        auto effectFlags = activeEffect->GetBaseObject()->data.flags;
        bool noDuration = ((effectFlags & RE::EffectSetting::EffectSettingData::Flag::kNoDuration) != RE::EffectSetting::EffectSettingData::Flag::kNone);
        bool noMagnitude = ((effectFlags & RE::EffectSetting::EffectSettingData::Flag::kNoMagnitude) != RE::EffectSetting::EffectSettingData::Flag::kNone);
        bool powerAffectsDuration = ((effectFlags & RE::EffectSetting::EffectSettingData::Flag::kPowerAffectsDuration) != RE::EffectSetting::EffectSettingData::Flag::kNone);
        bool powerAffectsMagnitude = ((effectFlags & RE::EffectSetting::EffectSettingData::Flag::kPowerAffectsMagnitude) != RE::EffectSetting::EffectSettingData::Flag::kNone);

        if ((!noDuration) && (powerAffectsDuration))
        {
            activeEffect->duration *= effectiveness;
        }
        
        if ((!noMagnitude) && (powerAffectsMagnitude))
        {
            float prevMagnitude = activeEffect->magnitude;
            float changedMagnitude = effectiveness * prevMagnitude;

            activeEffect->magnitude = (prevMagnitude >= 0.0) ? (std::max)(changedMagnitude, 1.0F) : (std::min)(changedMagnitude, -1.0F);
        }
    };
    
    void MagicEffectPotencyFlags::Restart(RE::ActiveEffect* activeEffect){

    };
} // namespace Patch