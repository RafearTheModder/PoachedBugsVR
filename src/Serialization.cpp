#include "Serialization.h"

#include "RE/Skyrim.h"
#include "dataHandler.h"
#include "Patches/Scrambled/EnchantmentCost.h"
#include "Patches/Scrambled/VendorRespawnFix.h"

namespace Serialization
{
	void Load(SKSE::SerializationInterface* serializationInterface)
    {
	    logger::info("Serialization::Load starting...");

		auto                    createdObjectManager = RE::BGSCreatedObjectManager::GetSingleton();
		RE::BSSpinLockGuard lockGuard(createdObjectManager->lock);

		std::uint32_t type, version, length;

		while (serializationInterface->GetNextRecordInfo(type, version, length))
		{
			switch (type)
			{
				case SerializationData::EnchantmentCost::kType:
				{
					if (!settings.enchantmentCost)
					{
						continue;
					}
    
                    if (version == SerializationData::EnchantmentCost::kVersion &&
                        length == sizeof(SerializationData::EnchantmentCost))
                    {
                        SerializationData::EnchantmentCost::Deserialize(serializationInterface);
                    }
                    else
                    {
			            logger::error(FMT_STRING("Type: {} validation failure, version = {}, length = {}."), type, version, length);
                    }
					break;
				}
				case SerializationData::LastDayRespawned::kType:
				{
					if (!settings.vendorRespawnFix)
					{
						continue;
					}

					if (version == SerializationData::LastDayRespawned::kVersion &&
						length == sizeof(SerializationData::LastDayRespawned))
					{
						SerializationData::LastDayRespawned::Deserialize(serializationInterface);
					}
					else
					{
						logger::error(FMT_STRING("Type: {} validation failure, version = {}, length = {}."), type, version, length);
					}
					break;
				}
				default:
				{
			        logger::error(FMT_STRING("Type mismatch, {}."), type);
				}
			}
		}

	    logger::info("Serialization::Load completed.");
    }

	void Save(SKSE::SerializationInterface* serializationInterface)
    {
	    logger::info("Serialization::Save starting...");

		if (settings.enchantmentCost)
		{
			auto createdObjectManager = RE::BGSCreatedObjectManager::GetSingleton();
			RE::BSSpinLockGuard lockGuard(createdObjectManager->lock);

			for (const auto& armorEnchantment : createdObjectManager->armorEnchantments)
			{
				SerializationData::EnchantmentCost::Serialize(serializationInterface, skyrim_cast<RE::EnchantmentItem*>(armorEnchantment.magicItem));
			}

			for (const auto& weaponEnchantment : createdObjectManager->weaponEnchantments)
			{
				SerializationData::EnchantmentCost::Serialize(serializationInterface, skyrim_cast<RE::EnchantmentItem*>(weaponEnchantment.magicItem));
			}
		}

		if (settings.vendorRespawnFix)
		{
			const auto& factions = RE::TESDataHandler::GetSingleton()->formArrays[static_cast<std::uint32_t>(RE::FormType::Faction)];

			for (auto* faction : factions)
			{
				SerializationData::LastDayRespawned::Serialize(serializationInterface, skyrim_cast<RE::TESFaction*>(faction));
			}
		}

	    logger::info("Serialization::Save completed.");
    }
}