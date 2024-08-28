/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "ArmorWeightModPerkEntry.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
    void ArmorWeightModPerkEntry::InstallPatch() {
        if(settings.armorWeightModPerkEntry)
        {
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::ArmorWeightModPerkEntry::GetInventoryWeight.address(), GetInventoryWeight);

            REL::Relocation<uintptr_t> BGSEntryPointPerkEntryVtable{ RE::VTABLE_BGSEntryPointPerkEntry[0] };
            applyPerkEntry_ = BGSEntryPointPerkEntryVtable.write_vfunc(0xA, ArmorWeightModPerkEntry::ApplyPerkEntry);
            removePerkEntry_ = BGSEntryPointPerkEntryVtable.write_vfunc(0xB, ArmorWeightModPerkEntry::RemovePerkEntry);

            logger::info("\"ArmorWeightModPerkEntry\" patch installed!");
        }
        else
        {
            logger::info("\"ArmorWeightModPerkEntry\" patch is NOT enabled... skipping.");
        }
    };

	void InventoryChangesResetWeight(RE::InventoryChanges* a_InventoryChanges)
	{
		a_InventoryChanges->armorWeight = a_InventoryChanges->totalWeight;
		a_InventoryChanges->totalWeight  = -1.0F;

		auto owner = a_InventoryChanges->owner;

		if (owner)
		{
			if (owner->formType == RE::FormType::ActorCharacter)
			{
				static_cast<RE::Actor*>(owner)->equippedWeight = -1.0F;
			}
		}
	};

	void ArmorWeightModPerkEntry::ApplyPerkEntry(RE::BGSEntryPointPerkEntry* entryPointPerkEntry, RE::Actor* perkOwner)
	{
		ArmorWeightModPerkEntry::applyPerkEntry_(entryPointPerkEntry, perkOwner);

		if (entryPointPerkEntry->entryData.entryPoint == RE::BGSPerkEntry::EntryPoint::kModArmorWeight)
		{
			auto inventoryChanges = perkOwner->GetInventoryChanges();

			if (inventoryChanges)
			{
				InventoryChangesResetWeight(inventoryChanges);
			}
		}
	}

	RE::InventoryEntryData* ArmorWeightModPerkEntry::GetInventoryEntryData(RE::InventoryChanges* inventoryChanges, RE::TESBoundObject* item)
	{
		auto inventoryEntryDataList = inventoryChanges->entryList;

		if (inventoryEntryDataList)
		{
			for (auto inventoryEntryData : *inventoryEntryDataList)
			{
				if (inventoryEntryData->object == item)
				{
					return inventoryEntryData;
				}
			}
		}

		return nullptr;
	}

	float ArmorWeightModPerkEntry::GetInventoryWeight(RE::InventoryChanges* inventoryChanges)
	{
		// inventoryChanges != nullptr

		if (inventoryChanges->totalWeight != -1.0F)
		{
			return inventoryChanges->totalWeight;
		}

		float inventoryWeight{ 0.0F };

		auto owner      = inventoryChanges->owner;
		auto ownerActor = owner && owner->formType == RE::FormType::ActorCharacter ? static_cast<RE::Actor*>(owner) : nullptr;
		auto container  = owner ? owner->GetContainer() : nullptr;
// for (std::uint32_t i = 0; i < containerObject->numContainerObjects; ++i) 
// {
		// TESContainer
		if (container)
		{
			for (std::uint32_t i = 0; i < container->numContainerObjects; ++i)
			{
				auto item = container->containerObjects[i]->obj;

				if (item)
				{
					auto itemWeight = item->GetWeight();

					if (itemWeight > 0.0F)
					{
						auto inventoryEntryData = ArmorWeightModPerkEntry::GetInventoryEntryData(inventoryChanges, item);
						auto itemCount          = container->containerObjects[i]->count;

						if (inventoryEntryData)
						{
							if (inventoryEntryData->IsQuestObject())
							{
								continue;
							}

							itemCount += inventoryEntryData->countDelta;

							if (itemCount > 0)
							{
								if (ownerActor)
								{
									if (item->formType == RE::FormType::Armor)
									{
										if (inventoryEntryData->IsWorn())
										{
											auto armorWeight = itemWeight;

											RE::BGSEntryPoint::HandleEntryPoint(RE::BGSPerkEntry::EntryPoint::kModArmorWeight, ownerActor, item, std::addressof(armorWeight));

											inventoryWeight += armorWeight;
											--itemCount;
										}
									}
								}
							}
						}

						inventoryWeight += itemCount * itemWeight;
					}
				}
			}
		}

		// InventoryChanges
		auto inventoryEntryDataList = inventoryChanges->entryList;

		if (inventoryEntryDataList)
		{
			for (auto inventoryEntryData : *inventoryEntryDataList)
			{
				auto item = inventoryEntryData->object;

				if (item)
				{
					bool hasItem = false;
					for (std::uint32_t i = 0; i < container->numContainerObjects; ++i)
					{
						if (container->containerObjects[i]->obj == item)
						{
							hasItem = true;
							i = container->numContainerObjects;
						}
					}
					if (hasItem)
					{
						continue;
					}

					if (inventoryEntryData->IsQuestObject())
					{
						continue;
					}

					auto itemWeight = item->GetWeight();

					if (itemWeight > 0.0F)
					{
						auto itemCount = inventoryEntryData->countDelta;

						if (itemCount > 0)
						{
							if (ownerActor)
							{
								if (item->formType == RE::FormType::Armor)
								{
									if (inventoryEntryData->IsWorn())
									{
										auto armorWeight = itemWeight;

										RE::BGSEntryPoint::HandleEntryPoint(RE::BGSPerkEntry::EntryPoint::kModArmorWeight, ownerActor, item, std::addressof(armorWeight));

										inventoryWeight += armorWeight;
										--itemCount;
									}
								}
							}

							inventoryWeight += itemCount * itemWeight;
						}
					}
				}
			}
		}

		inventoryChanges->totalWeight = inventoryWeight;

		if (ownerActor)
		{
			ownerActor->HandleActorValueModified(RE::ActorValue::kInventoryWeight, inventoryChanges->armorWeight, inventoryWeight - inventoryChanges->armorWeight, nullptr);
		}

		return inventoryChanges->totalWeight;
	}

	void ArmorWeightModPerkEntry::RemovePerkEntry(RE::BGSEntryPointPerkEntry* entryPointPerkEntry, RE::Actor* perkOwner)
	{
		ArmorWeightModPerkEntry::removePerkEntry_(entryPointPerkEntry, perkOwner);

		if (entryPointPerkEntry->entryData.entryPoint == RE::BGSPerkEntry::EntryPoint::kModArmorWeight)
		{
			auto inventoryChanges = perkOwner->GetInventoryChanges();

			if (inventoryChanges)
			{
				InventoryChangesResetWeight(inventoryChanges);
			}
		}
	}

	REL::Relocation<decltype(&ArmorWeightModPerkEntry::ApplyPerkEntry)>  ArmorWeightModPerkEntry::applyPerkEntry_{};
	REL::Relocation<decltype(&ArmorWeightModPerkEntry::RemovePerkEntry)> ArmorWeightModPerkEntry::removePerkEntry_{};
} // namespace Patch