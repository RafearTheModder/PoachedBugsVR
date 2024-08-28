/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class ArmorWeightModPerkEntry
    {
    public:
        static void InstallPatch();

    private:
		static void                        ApplyPerkEntry(RE::BGSEntryPointPerkEntry* entryPointPerkEntry, RE::Actor* perkOwner);
		static RE::InventoryEntryData*     GetInventoryEntryData(RE::InventoryChanges* inventoryChanges, RE::TESBoundObject* item);
		static float                       GetInventoryWeight(RE::InventoryChanges* inventoryChanges);
		static void                        RemovePerkEntry(RE::BGSEntryPointPerkEntry* entryPointPerkEntry, RE::Actor* perkOwner);

		static REL::Relocation<decltype(&ArmorWeightModPerkEntry::ApplyPerkEntry)>  applyPerkEntry_;
		static REL::Relocation<decltype(&ArmorWeightModPerkEntry::RemovePerkEntry)> removePerkEntry_;
    };
} // namespace Patch