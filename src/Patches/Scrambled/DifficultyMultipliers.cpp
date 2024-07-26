/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "Patches/Scrambled/DifficultyMultipliers.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
	void DifficultyMultipliers::InstallPatch()
	{
		if(settings.difficultyMultipliers.commandedActors || settings.difficultyMultipliers.teammates){
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::Actor::AdjustHealthDamageToDifficulty.address(), AdjustHealthDamageToDifficulty);

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::DifficultyMultipliers::DamageHealth.address(), DamageHealth);
			
			if(settings.difficultyMultipliers.commandedActors){
            	logger::info("\"DifficultyMultipliers.commandedActors\" patch installed!");
			}
			if(settings.difficultyMultipliers.teammates){
            	logger::info("\"DifficultyMultipliers.teammates\" patch installed!");
			}
		}
		else{
            logger::info("\"DifficultyMultipliers.commandedActors\" patch is NOT enabled... skipping.");
            logger::info("\"DifficultyMultipliers.teammates\" patch is NOT enabled... skipping.");
		}
	}

	float DifficultyMultipliers::AdjustHealthDamageToDifficulty(RE::Actor* target, float damage, float onlyReduceDamage)
	{
		auto* player               = RE::PlayerCharacter::GetSingleton();
		auto  difficultyMultiplier = RE::PlayerCharacter::GetDifficultyMultiplier(
            player->difficulty,
            RE::ActorValue::kHealth,
            target == player || (settings.difficultyMultipliers.teammates && DifficultyMultipliers::IsTeammate(target)) || (settings.difficultyMultipliers.commandedActors && DifficultyMultipliers::IsCommandedActor(target)));

		return std::abs(onlyReduceDamage) <= 0.0001F || difficultyMultiplier < 1.0F ? difficultyMultiplier * damage : damage;
	}

	bool DifficultyMultipliers::DamageHealth(RE::Actor* target, float damage, RE::Actor* attacker, bool onlyReduceDamage)
	{
		// target != nullptr
		// attacker != nullptr

		if (target->IsInvulnerable() || target->boolFlags.all(RE::Actor::BOOL_FLAGS::kIsInKillMove))
		{
			return false;
		}

		if (target->actorState1.lifeState == RE::ACTOR_LIFE_STATE::kEssentialDown && target->CanBeKilledBy(attacker))
		{
			target->actorState1.lifeState = RE::ACTOR_LIFE_STATE::kAlive;
		}

		auto adjustedDamage = -target->AdjustHealthDamageToDifficulty(-damage, static_cast<float>(onlyReduceDamage));

		if (adjustedDamage > 0.0F)
		{
			auto* targetCombatController = target->combatController;

			if (targetCombatController)
			{
				targetCombatController->DamagedByAttacker(attacker, adjustedDamage);
			}

			if (target != RE::PlayerCharacter::GetSingleton())
			{
				auto* targetCurrentProcess = target->currentProcess;

				if (targetCurrentProcess && target->boolFlags.none(RE::Actor::BOOL_FLAGS::kEssential) && target->CanBeKilledBy(attacker))
				{
					targetCurrentProcess->ModifyTrackedDamage(attacker, adjustedDamage);
				}
			}

			target->ModifyActorValue(RE::ACTOR_VALUE_MODIFIER::kDamage, RE::ActorValue::kHealth, -adjustedDamage, attacker);

			if (RE::TaskQueueInterface::ShouldUseTaskQueue())
			{
				RE::TaskQueueInterface::GetSingleton()->QueueScriptFunctionCall(RE::ScriptOutput::kDamageObject, target, damage);
			}
			else
			{
				target->DamageObject(damage, false);
			}
		}

		return target->IsDead(false);
	}

	bool DifficultyMultipliers::IsCommandedActor(RE::Actor* actor)
	{
		return actor->GetCommandingActor().get() == RE::PlayerCharacter::GetSingleton();
	}

	bool DifficultyMultipliers::IsTeammate(RE::Actor* actor)
	{
		return actor->IsPlayerTeammate();
	}
}
