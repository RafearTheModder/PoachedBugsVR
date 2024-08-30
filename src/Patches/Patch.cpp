#include "Patch.h"
#include "dataHandler.h"
#include "DrawnBowDetection.h"

// Patches below this line ultimately originate from Kernal's Scrambled Bugs. See README.MD for the licensing implications of this.
#include "Scrambled/ReflectDamage.h"
#include "Scrambled/ScrollExp.h"
#include "Scrambled/PoisonResistance.h"
#include "Scrambled/StaffExp.h"
#include "Scrambled/ImproveAllEnchantmentEffects.h"
#include "Scrambled/PerkEntryMultipleSpellsApplication.h"
#include "Scrambled/PerkEntrySpellCasterCorrection.h"
#include "Scrambled/PowerAttackStaminaRequirement.h"
#include "Scrambled/AccumulateMagnitudeScaling.h"
#include "Scrambled/ResetHarvestFlags.h"
#include "Scrambled/LevelledCharacter.h"
#include "Scrambled/WeaponCharge.h"
#include "Scrambled/DifficultyMultipliers.h"
#include "Scrambled/EnchantmentCost.h"
#include "Scrambled/ActorValuePercentage.h"
#include "Scrambled/ArmorWeightModPerkEntry.h"
#include "Scrambled/TrainingMenu.h"

namespace Patch
{
    void InstallAllPatches()
    {
        DrawnBowDetection::InstallPatch();

        // Patches below this line ultimately originate from Kernal's Scrambled Bugs. See README.MD for the licensing implications of this.
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
        LevelledCharacter::InstallPatch();
        WeaponCharge::InstallPatch();
        DifficultyMultipliers::InstallPatch();
        EnchantmentCost::InstallPatch();
        ActorValuePercentage::InstallPatch();
        ArmorWeightModPerkEntry::InstallPatch();
        TrainingMenu::InstallPatch();
    }
} // namespace Patch