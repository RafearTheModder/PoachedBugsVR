#include "Patch.h"
#include "dataHandler.h"
#include "ReflectDamagePatch.h"
#include "ScrollExpPatch.h"

namespace Patch
{
    void InstallAllPatches()
    {
        ReflectDamagePatch::InstallPatch();
        ScrollExpPatch::InstallPatch();
    }
} // namespace Patch