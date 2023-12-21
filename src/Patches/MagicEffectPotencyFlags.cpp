#include "MagicEffectPotencyFlags.h"

#include "Addresses.h"

namespace Patch
{
    /*TODO: Implement MagicEffectPotencyFlags
            This patch will force the game to actually respect the "power affects magnitude/duration" and "no magnitude/duration" flags
            labels: Type:Feature, Status:Backlog, Priority:2*/
    void MagicEffectPotencyFlags::InstallPatch() {
        if(settings.magicEffectPotencyFlags)
        {
            logger::info("\"MagicEffectPotencyFlags\" patch installed!");
        }
        else
        {
            logger::info("\"MagicEffectPotencyFlags\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch