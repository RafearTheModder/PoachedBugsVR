/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "Patches/Scrambled/EnchantmentCost.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
	void EnchantmentCost::InstallPatch()
	{
		if(settings.enchantmentCost){
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_call<5>(RE::Address::EnchantmentCost::Compare.address(), Compare);

			logger::info("\"EnchantmentCost\" patch installed!");
		}
		else{
            logger::info("\"EnchantmentCost\" patch is NOT enabled... skipping.");
		}
	}

	bool EnchantmentCost::Compare(RE::Effect* left, RE::Effect* right)
	{
		if (left->baseEffect != right->baseEffect)
		{
			return true;
		}

		if (left->GetMagnitude() != right->GetMagnitude())
		{
			return true;
		}

		if (left->GetArea() != right->GetArea())
		{
			return true;
		}

		if (left->GetDuration() != right->GetDuration())
		{
			return true;
		}

		return false;
	}
}

namespace SerializationData
{

	bool EnchantmentCost::Deserialize(SKSE::SerializationInterface* serializationInterface)
	{
		EnchantmentCost record;
		serializationInterface->ReadRecordData(record);

		if (!serializationInterface->ResolveFormID(record.formID, record.formID))
		{
			logger::error(FMT_STRING("Failed to resolve form ID, 0x{:X}."), record.formID);

			return false;
		}

		auto enchantment = skyrim_cast<RE::EnchantmentItem*>(RE::TESForm::LookupByID(record.formID));

		if (!enchantment || enchantment->formType != RE::FormType::Enchantment)
		{
			logger::error(FMT_STRING("Enchantment not found, form ID 0x{:X}."), record.formID);

			return false;
		}

		auto enchantmentItemData = &(enchantment->data);

		if (!enchantmentItemData)
		{
			logger::error(FMT_STRING("Data not found, form ID 0x{:X}."), record.formID);

			return false;
		}

		enchantmentItemData->costOverride      = record.enchantmentCost;
		enchantmentItemData->flags             = record.enchantmentItemFlags;

		return true;
	}

	bool EnchantmentCost::Serialize(SKSE::SerializationInterface* serializationInterface, RE::EnchantmentItem* enchantment)
	{
		if (!enchantment)
		{
			logger::error("Enchantment not found.");

			return false;
		}

		auto enchantmentItemData = &(enchantment->data);

		if (!enchantmentItemData)
		{
			logger::error("Data not found.");

			return false;
		}

		EnchantmentCost record;
		record.formID               = enchantment->formID;
		record.enchantmentCost      = enchantment->data.costOverride;
		record.enchantmentItemFlags = enchantment->data.flags;

		serializationInterface->WriteRecord(EnchantmentCost::kType, EnchantmentCost::kVersion, record);

		return true;
	}
}
