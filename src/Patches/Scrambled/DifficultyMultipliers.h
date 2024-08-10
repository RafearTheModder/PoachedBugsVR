/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
	class DifficultyMultipliers
	{
	public:
		static void InstallPatch();

	private:
		static float AdjustHealthDamageToDifficulty(RE::Actor* target, float damage, float onlyReduceDamage);
		static bool  IsCommandedActor(RE::Actor* actor);
		static bool  IsTeammate(RE::Actor* actor);
	};
}
