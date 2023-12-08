#include "ReflectDamage.h"

#include "Addresses.h"

namespace Patch
{
    void ReflectDamage::InstallPatch() {
        if(settings.reflectDamageLimitRemoval)
        {
            SKSE::AllocTrampoline(1 << 4);
            REL::safe_write(RE::Address::ReflectDamage::CompareReflectDamageAV.address(), REL::NOP2, 2);
            logger::info("\"Reflect damage limit removal\" patch installed!");
        }
        else
        {
            logger::info("\"Reflect damage limit removal\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch