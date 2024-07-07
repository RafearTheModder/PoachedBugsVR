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