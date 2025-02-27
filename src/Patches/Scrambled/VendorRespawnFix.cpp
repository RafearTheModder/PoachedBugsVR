/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "Patches/Scrambled/VendorRespawnFix.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
	void VendorRespawnFix::InstallPatch()
	{
		if(settings.vendorRespawnFix){
			logger::info("\"VendorRespawnFix\" patch installed!");
		}
		else{
            logger::info("\"VendorRespawnFix\" patch is NOT enabled... skipping");
		}
	}
}

namespace SerializationData
{

	bool LastDayRespawned::Deserialize(SKSE::SerializationInterface* serializationInterface)
	{
		LastDayRespawned record;
		serializationInterface->ReadRecordData(record);

		if (!serializationInterface->ResolveFormID(record.formID, record.formID))
		{
			logger::error("Failed to resolve form ID, 0x{:X}.", record.formID);

			return false;
		}

		auto faction = skyrim_cast<RE::TESFaction*>(RE::TESForm::LookupByID(record.formID));

		if (!faction || faction->formType != RE::FormType::Faction)
		{
			logger::error("Faction not found, form ID 0x{:X}.", record.formID);

			return false;
		}

		if (!faction->vendorData.merchantContainer)
		{
			logger::error("Merchant container not found, form ID 0x{:X}.", record.formID);

			return false;
		}

		faction->vendorData.lastDayReset = record.lastDayRespawned;

		return true;
	}

	bool LastDayRespawned::Serialize(SKSE::SerializationInterface* serializationInterface, RE::TESFaction* faction)
	{
		if (!faction)
		{
			logger::error("Faction not found.");

			return false;
		}

		if (!faction->vendorData.merchantContainer)
		{
			return false;
		}

		LastDayRespawned record;
		record.formID           = faction->formID;
		record.lastDayRespawned = faction->vendorData.lastDayReset;

		serializationInterface->WriteRecord(LastDayRespawned::kType, LastDayRespawned::kVersion, record);

		return true;
	}
}
