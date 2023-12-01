#include "Patch.h"
#include "dataHandler.h"
#include "ReflectDamage.h"
#include "ScrollExp.h"
#include "PoisonResistance.h"

namespace Patch
{
    void InstallAllPatches()
    {
        ReflectDamage::InstallPatch();
        ScrollExp::InstallPatch();
        PoisonResistance::InstallPatch();
    }
} // namespace Patch