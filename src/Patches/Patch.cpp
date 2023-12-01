#include "Patch.h"
#include "dataHandler.h"
#include "ReflectDamage.h"
#include "ScrollExp.h"

namespace Patch
{
    void InstallAllPatches()
    {
        ReflectDamage::InstallPatch();
        ScrollExp::InstallPatch();
    }
} // namespace Patch