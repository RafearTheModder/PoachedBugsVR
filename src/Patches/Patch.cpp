#include "Patch.h"
#include "dataHandler.h"
#include "ReflectDamage.h"
#include "ScrollExp.h"
#include "PoisonResistance.h"
#include "StaffExp.h"
#include "ImproveAllEnchantmentEffects.h"
#include "PerkEntryMultipleSpellsApplication.h"
#include "PerkEntrySpellCasterCorrection.h"
#include "PowerAttackStaminaRequirement.h"
#include "AccumulateMagnitudeScaling.h"
#include "ResetHarvestFlags.h"

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
        PowerAttackStaminaRequirement::InstallPatch();
        AccumulateMagnitudeScaling::InstallPatch();
        ResetHarvestFlags::InstallPatch();
    }
} // namespace Patch