#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class PoisonResistance
    {
    public:
        static void InstallPatch();
    private:
        static float CheckResistance(RE::MagicTarget* a_magicTarget, RE::MagicItem* a_magicItem, RE::Effect* a_effect, RE::TESBoundObject* a_object);
    };
} // namespace Patch