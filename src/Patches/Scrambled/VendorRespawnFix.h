/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
	class VendorRespawnFix
	{
	public:
		static void InstallPatch();
    };
}

namespace SerializationData
{
	struct LastDayRespawned
	{
		enum : std::uint32_t
		{
			kType    = 'LDR',
			kVersion = 1
		};

		static bool Deserialize(SKSE::SerializationInterface* serializationInterface);
		static bool Serialize(SKSE::SerializationInterface* serializationInterface, RE::TESFaction* faction);

		RE::FormID    formID;                // 0
		std::uint32_t lastDayRespawned;      // 4
	};
	static_assert(offsetof(LastDayRespawned, formID) == 0x0);
	static_assert(offsetof(LastDayRespawned, lastDayRespawned) == 0x4);
	static_assert(sizeof(LastDayRespawned) == 0x8);
}
