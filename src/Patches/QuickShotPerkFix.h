#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class QuickShotPerkFix
    {
    public:
        static void InstallPatch();
    private:
        static float GetBowPower(float drawTime, float bowSpeed);
    };
} // namespace Patch