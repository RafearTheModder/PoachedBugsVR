#include "ScrollExp.h"

namespace Patch
{
    void ScrollExp::InstallPatch() {
        if(settings.scrollsGrantExperience)
        {
            // Replace ScrollItem::GetSkillUsageData with SpellItem::GetSkillUsageData
            REL::Relocation<uintptr_t> scrollPatch{ REL::ID(228867) }; // ScrollItem::VirtualFunctionTable, index 60 contains GetSkillUsageData
            REL::Relocation<uintptr_t> spellItemPatch{ REL::ID(228888) }; // SpellItem::VirtualFunctionTable, index 60 contains GetSkillUsageData
            REL::safe_write(reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(scrollPatch.address())[0x60])), reinterpret_cast<std::uintptr_t*>(spellItemPatch.address())[0x60]);
            logger::info("\"Scrolls grant experience\" patch installed!");
        }
        else
        {
            logger::info("\"Scrolls grant experience\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch