#include "Patch.h"
#include "dataHandler.h"
#include "ReflectDamage.h"
#include "ScrollExp.h"
#include "PoisonResistance.h"
#include "StaffExp.h"
#include "ImproveAllEnchantmentEffects.h"
#include "PerkEntryMultipleSpellsApplication.h"
#include "PerkEntrySpellCasterCorrection.h"

namespace Patch
{
    void InstallAllPatches()
    {
        ReflectDamage::InstallPatch();
        ScrollExp::InstallPatch();
        PoisonResistance::InstallPatch();
        StaffExp::InstallPatch();
        ImproveAllEnchantmentEffects::InstallPatch();
        PerkEntryMultipleSpellsApplication::InstallPatch();
        PerkEntrySpellCasterCorrection::InstallPatch();
    }
} // namespace Patch