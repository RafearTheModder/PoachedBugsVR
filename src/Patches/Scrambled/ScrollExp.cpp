/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "ScrollExp.h"

namespace Patch
{
    void ScrollExp::InstallPatch() {
        if(settings.scrollsGrantExperience)
        {
            // Replace ScrollItem::GetSkillUsageData with SpellItem::GetSkillUsageData
            REL::safe_write(reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(RE::VTABLE_ScrollItem[0].address())[0x60])),
                            reinterpret_cast<std::uintptr_t*>(RE::VTABLE_SpellItem[0].address())[0x60]);
            logger::info("\"Scrolls grant experience\" patch installed!");
        }
        else
        {
            logger::info("\"Scrolls grant experience\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch