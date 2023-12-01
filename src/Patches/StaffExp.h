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
    };
} // namespace Patch