#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class MagicEffectPotencyFlags
    {
    public:
        static void InstallPatch();
    private:
        static void Adjust(RE::ActiveEffect* activeEffect, float effectiveness, bool requireHostility);
        static void Restart(RE::ActiveEffect* activeEffect);
    };
} // namespace Patch
