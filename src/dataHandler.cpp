#include "dataHandler.h"

settingsStorage settings{};

void dataHandler::readSettings() {
	logger::info("reading settings");
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\PoachedBugsVR.ini"
	ini.LoadFile(SETTINGFILE_PATH);

	// (Relatively) safe fixes
	settings.resetHarvestFlags = ini.GetBoolValue("Fixes", "resetHarvestFlags", true);
	settings.improveAllEnchantmentEffects = ini.GetBoolValue("Fixes", "improveAllEnchantmentEffects", true);
	settings.perkEntrySpellCasterFix = ini.GetBoolValue("Fixes", "perkEntrySpellCasterFix", true);
	settings.powerAttacksStaminaRequirementNPC = ini.GetBoolValue("Fixes", "powerAttacksStaminaRequirementNPC", true);
	// The player side of the power attack stamina patch may conflict with Planck, and will definitely be useless with it redoing the power attack code.
	settings.powerAttacksStaminaRequirementPlayer = ini.GetBoolValue("Fixes", "powerAttacksStaminaRequirementPlayer", false);
	settings.drawnBowDetection = ini.GetBoolValue("Fixes", "drawnBowDetection", true);

	// Tweaks with extra dependence/compatibility concerns
	settings.poisonsUseOtherResistances = ini.GetBoolValue("Tweaks", "poisonsUseOtherResistances", false);
	settings.scrollsGrantExperience = ini.GetBoolValue("Tweaks", "scrollsGrantExperience", false);
	settings.stavesGrantExperience = ini.GetBoolValue("Tweaks", "stavesGrantExperience", false);
	settings.staffExperienceIgnoresEnchantmentCost = ini.GetBoolValue("Tweaks", "staffExperienceIgnoresEnchantmentCost", false);
	settings.perkEntryMultipleSpellsApplication = ini.GetBoolValue("Tweaks", "perkEntryMultipleSpellsApplication", false);
	settings.accumulateMagnitudeScaling = ini.GetBoolValue("Tweaks", "accumulateMagnitudeScaling", false);
	settings.reflectDamageLimitRemoval = ini.GetBoolValue("Tweaks", "reflectDamageLimitRemoval", true);

	// Advanced settings that control details of the behavior of other patches if enabled
	settings.drawnBowSettings.startThreshold = ini.GetDoubleValue("DrawnBow", "startThreshold", 0.2);
	settings.drawnBowSettings.midThreshold = ini.GetDoubleValue("DrawnBow", "midThreshold", 0.4);
	settings.drawnBowSettings.completeThreshold = ini.GetDoubleValue("DrawnBow", "completeThreshold", 0.8);
}
