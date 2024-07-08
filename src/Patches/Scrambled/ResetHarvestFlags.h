/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class ResetHarvestFlags
    {
    public:
        static void InstallPatch();
    private:
        static void SetEmpty(RE::TESObjectREFR* object, bool empty);
        
		static REL::Relocation<decltype(ResetHarvestFlags::SetEmpty)> originalSetEmpty;
    };
} // namespace Patch
