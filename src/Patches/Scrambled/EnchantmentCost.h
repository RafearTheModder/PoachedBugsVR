/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
	class EnchantmentCost
	{
	public:
		static void InstallPatch();

	private:
		static bool Compare(RE::Effect* left, RE::Effect* right);
	};
}

namespace SerializationData
{
	struct EnchantmentCost
	{
		enum : std::uint32_t
		{
			kType    = 'ENCH', // ECST
			kVersion = 1
		};

		static bool Deserialize(SKSE::SerializationInterface* serializationInterface);
		static bool Serialize(SKSE::SerializationInterface* serializationInterface, RE::EnchantmentItem* enchantment);

		RE::FormID                                                                  formID;               // 0
		std::int32_t                                                                enchantmentCost;      // 4
		SKSE::stl::enumeration<RE::EnchantmentItem::EnchantmentFlag, std::uint32_t> enchantmentItemFlags; // 8
	};
	static_assert(offsetof(EnchantmentCost, formID) == 0x0);
	static_assert(offsetof(EnchantmentCost, enchantmentCost) == 0x4);
	static_assert(offsetof(EnchantmentCost, enchantmentItemFlags) == 0x8);
	static_assert(sizeof(EnchantmentCost) == 0xC);
}
