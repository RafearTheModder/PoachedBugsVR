/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "ImproveAllEnchantmentEffects.h"

namespace Patch
{
    void ImproveAllEnchantmentEffects::InstallPatch() {
        if(settings.improveAllEnchantmentEffects)
        {
            REL::Relocation<uintptr_t> enchantmentItemVtable{ RE::VTABLE_CraftingSubMenus__EnchantConstructMenu__CreateEffectFunctor[0] }; // index 1 of this vtable has the functor we are looking for
            originalAddEffect_ = enchantmentItemVtable.write_vfunc(0x1, ImproveAllEnchantmentEffects::AddEffect);
            logger::info("\"ImproveAllEnchantmentEffects\" patch installed!");
        }
        else
        {
            logger::info("\"ImproveAllEnchantmentEffects\" patch is NOT enabled... skipping.");
        }
    };
    
    RE::BSContainer::ForEachResult ImproveAllEnchantmentEffects::AddEffect(RE::CraftingSubMenus::EnchantConstructMenu::CreateEffectFunctor* createEffectFunctor, RE::Effect* effect){
        RE::Effect* actualCostliestEffect = createEffectFunctor->costliestEffect;
        createEffectFunctor->costliestEffect = effect;

        auto retval = originalAddEffect_(createEffectFunctor, effect);

        createEffectFunctor->costliestEffect = actualCostliestEffect;

        return retval;
    };

    REL::Relocation<decltype(ImproveAllEnchantmentEffects::AddEffect)> ImproveAllEnchantmentEffects::originalAddEffect_{};
} // namespace Patch