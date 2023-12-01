#include "ReflectDamagePatch.h"

namespace Patch
{
    void ReflectDamagePatch::InstallPatch() {
        if(settings.reflectDamageLimitRemoval)
        {
            REL::Relocation<uintptr_t> patch{ REL::ID(42842) };
            SKSE::AllocTrampoline(1 << 4);
            REL::safe_write(patch.address() + 0x761, REL::NOP8, 8);
            logger::info("\"Reflect damage limit removal\" patch installed!");
        }
        else
        {
            logger::info("\"Reflect damage limit removal\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch