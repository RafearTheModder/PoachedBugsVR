/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class ImproveAllEnchantmentEffects
    {
    public:
        static void InstallPatch();
    private:
        static RE::BSContainer::ForEachResult AddEffect(RE::CraftingSubMenus::EnchantConstructMenu::CreateEffectFunctor* createEffectFunctor, RE::Effect* effect);
    
        static REL::Relocation<decltype(ImproveAllEnchantmentEffects::AddEffect)> originalAddEffect_;
    };
} // namespace Patch