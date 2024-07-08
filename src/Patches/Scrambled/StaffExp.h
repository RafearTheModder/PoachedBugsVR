/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class StaffExp
    {
    public:
        static void InstallPatch();
    private:
        static bool EnchantmentGetSkillData(RE::EnchantmentItem* enchant, RE::MagicItem::SkillUsageData& skillUsage);
        static bool StaffEnchantmentGetSkillData(RE::EnchantmentItem* enchant, RE::MagicItem::SkillUsageData& skillUsage);

        static REL::Relocation<decltype(StaffExp::EnchantmentGetSkillData)> originalEnchantmentGetSkillData_;
        static decltype(StaffExp::EnchantmentGetSkillData)* spellItemGetSkillData_;
    };
} // namespace Patch