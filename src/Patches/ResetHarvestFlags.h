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
