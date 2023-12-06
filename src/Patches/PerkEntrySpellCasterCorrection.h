#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class PerkEntrySpellCasterCorrection
    {
    public:
        static void InstallPatch();
    private:
        static void ApplySpell(RE::Actor* target, RE::SpellItem* spell, RE::Actor* caster);
    };
} // namespace Patch