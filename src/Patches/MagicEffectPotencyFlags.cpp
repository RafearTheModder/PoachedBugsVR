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
            /*TODO: Clean this up with helper functions (or switch to xbyak after I learn how to properly use it?)
                    This structure base approach is very messy, but should function well enough
                    labels: Type:Refactoring, Status:Backlog, Priority:3*/
			struct AbsoluteJumpAssembly
			{
				// jmp [addr]
				std::uint8_t  jmp = 0xFF;
				std::uint8_t  modrm = 0x25;
				std::int32_t  disp = 0x0;
				std::uint64_t addr;

                AbsoluteJumpAssembly(std::uintptr_t dst_addr){
                    addr = dst_addr;
                }
			};
            auto adjustJmp = AbsoluteJumpAssembly(reinterpret_cast<std::uintptr_t>(std::addressof(MagicEffectPotencyFlags::Adjust)));
            REL::safe_write(RE::Address::MagicEffect::Adjust.address(), &adjustJmp, sizeof(adjustJmp));
            auto restartJmp = AbsoluteJumpAssembly(reinterpret_cast<std::uintptr_t>(std::addressof(MagicEffectPotencyFlags::Restart)));
            REL::safe_write(RE::Address::MagicEffect::Restart.address(), &restartJmp, sizeof(restartJmp));
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
        activeEffect->elapsedSeconds = 0.0;

        RE::EffectSetting* baseEffect = activeEffect->GetBaseObject();
        RE::Actor* caster = activeEffect->caster.get().get();
        if (!baseEffect || !caster)
        {
            return;
        }

        bool wasDualCast = ((activeEffect->flags & RE::ActiveEffect::Flag::kDual) == RE::ActiveEffect::Flag::kDual);
        bool isDualCasting = caster->GetHighProcess() ? caster->GetHighProcess()->isDualCasting : false;

        if (isDualCasting != wasDualCast)
        {
            activeEffect->flags ^= RE::ActiveEffect::Flag::kDual; // Use xor to simply flip the flag
            RE::MagicItem* spell = activeEffect->spell;
            float cost = spell->CalculateMagickaCost(caster);

            float effectiveness = caster->GetDualCastingEffectiveness(cost);
            if(wasDualCast)
            {
                //If the spell *was* dual cast but we are hitting this, it no longer *is* dual cast. So we need to invert the effectiveness mod that entails
                effectiveness = 1.0/effectiveness;
            }

            MagicEffectPotencyFlags::Adjust(activeEffect, effectiveness, false);
        }
    };
} // namespace Patch