#include "ImproveAllEnchantmentEffects.h"

namespace Patch
{
    void ImproveAllEnchantmentEffects::InstallPatch() {
        if(settings.improveAllEnchantmentEffects)
        {
            REL::Relocation<uintptr_t> enchantmentItemVtable{ RE::VTABLE_CraftingSubMenus__EnchantConstructMenu__CreateEffectFunctor[0] }; // index 1 of this vtable has the functor we are looking for
            originalAddEffect_ = enchantmentItemVtable.write_vfunc(0x1, ImproveAllEnchantmentEffects::AddEffect);
            logger::info("\"Improve multiple enchantment effects\" patch installed!");
        }
        else
        {
            logger::info("\"Improve multiple enchantment effects\" patch is NOT enabled... skipping.");
        }
    };
    
    RE::BSContainer::ForEachResult ImproveAllEnchantmentEffects::AddEffect(RE::CraftingSubMenus::EnchantConstructMenu::CreateEffectFunctor* createEffectFunctor, RE::Effect* effect){
        logger::info("ImproveAllEnchantmentEffects::AddEffect - Begin");
        logger::info(FMT_STRING("                                        - createEffectFunctor->createdEffects.size() = {}"), createEffectFunctor->createdEffects.size());
        logger::info(FMT_STRING("                                        - effect->effectItem.magnitude = {}"), effect->effectItem.magnitude);
        logger::info(FMT_STRING("                                        - effect->effectItem.area = {}"), effect->effectItem.area);
        logger::info(FMT_STRING("                                        - effect->effectItem.duration = {}"), effect->effectItem.duration);
        RE::Effect* actualCostliestEffect = createEffectFunctor->costliestEffect;

        // logger::info(FMT_STRING("                                        - createEffectFunctor->costliestEffect = {}"), createEffectFunctor->costliestEffect);
        logger::info("                                        - temporarily swapping costliest effect to force-trigger power scaling...");
        createEffectFunctor->costliestEffect = effect;
        // logger::info(FMT_STRING("                                        - createEffectFunctor->costliestEffect = {}"), createEffectFunctor->costliestEffect);

        logger::info("                                        - originalAddEffect_()");
        auto retval = originalAddEffect_(createEffectFunctor, effect);

        // logger::info(FMT_STRING("                                        - createEffectFunctor->costliestEffect = {}"), createEffectFunctor->costliestEffect);
        logger::info("                                        - restoring original costliest effect to avoid unwanted side-effects...");
        createEffectFunctor->costliestEffect = actualCostliestEffect;
        // logger::info(FMT_STRING("                                        - createEffectFunctor->costliestEffect = {}"), createEffectFunctor->costliestEffect);

        logger::info(FMT_STRING("                                        - createEffectFunctor->createdEffects.size() = {}"), createEffectFunctor->createdEffects.size());
        logger::info(FMT_STRING("                                        - effect->effectItem.magnitude = {}"), effect->effectItem.magnitude);
        logger::info(FMT_STRING("                                        - effect->effectItem.area = {}"), effect->effectItem.area);
        logger::info(FMT_STRING("                                        - effect->effectItem.duration = {}"), effect->effectItem.duration);
        if (createEffectFunctor->createdEffects.size() > 0)
        {
            logger::info(FMT_STRING("                                        - createEffectFunctor->createdEffects[createEffectFunctor->createdEffects.size()-1].effectItem.magnitude = {}"), createEffectFunctor->createdEffects[createEffectFunctor->createdEffects.size()-1].effectItem.magnitude);
            logger::info(FMT_STRING("                                        - createEffectFunctor->createdEffects[createEffectFunctor->createdEffects.size()-1].effectItem.area = {}"), createEffectFunctor->createdEffects[createEffectFunctor->createdEffects.size()-1].effectItem.area);
            logger::info(FMT_STRING("                                        - createEffectFunctor->createdEffects[createEffectFunctor->createdEffects.size()-1].effectItem.duration = {}"), createEffectFunctor->createdEffects[createEffectFunctor->createdEffects.size()-1].effectItem.duration);
        }
 
        logger::info("ImproveAllEnchantmentEffects::AddEffect - End");
        return retval;
    };

    REL::Relocation<decltype(ImproveAllEnchantmentEffects::AddEffect)> ImproveAllEnchantmentEffects::originalAddEffect_{};
} // namespace Patch