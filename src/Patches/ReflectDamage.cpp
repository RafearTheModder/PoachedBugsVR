#include "ReflectDamage.h"

namespace Patch
{
    void ReflectDamage::InstallPatch() {
        if(settings.reflectDamageLimitRemoval)
        {
            REL::Relocation<uintptr_t> patch{ REL::ID(42842) };
            SKSE::AllocTrampoline(1 << 4);
            REL::safe_write(patch.address() + 0x761, REL::NOP2, 2);
            logger::info("\"Reflect damage limit removal\" patch installed!");
        }
        else
        {
            logger::info("\"Reflect damage limit removal\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch