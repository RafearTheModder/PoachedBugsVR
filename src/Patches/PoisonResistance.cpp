#include "PoisonResistance.h"

namespace Patch
{
    void PoisonResistance::InstallPatch() {
        if(settings.poisonsUseOtherResistances)
        {
            logger::info("Warning: \"Poison resistance\" patch is not implemented fully yet!");
        }
        else
        {
            logger::info("\"Poison resistance\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch