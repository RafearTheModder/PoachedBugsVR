#include "ReflectDamagePatch.h"

namespace Patch
{
    void ReflectDamagePatch::InstallPatch() {
        if(settings.reflectDamageLimitRemoval)
        {
            REL::Relocation<uintptr_t> patch{ REL::ID(42842) };
            SKSE::AllocTrampoline(1 << 4);
            // 0x761 offset from REL::ID(42842) marks the beginning of a section of code that caps reflect damage within a hit event to a maximum of 100%.
            //    Replacing this section with a NOP8 elimates the cap and allows the full raw value to flow through to the return damage calculation afterwards.
            REL::safe_write(patch.address() + 0x761, REL::NOP8, 8);
            logger::info("\"Reflect damage limit removal\" patch installed!");
        }
        else
        {
            logger::info("\"Reflect damage limit removal\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch