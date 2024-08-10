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

	bool DifficultyMultipliers::IsCommandedActor(RE::Actor* actor)
	{
		return actor->GetCommandingActor().get() == RE::PlayerCharacter::GetSingleton();
	}

	bool DifficultyMultipliers::IsTeammate(RE::Actor* actor)
	{
		return actor->IsPlayerTeammate();
	}
}
