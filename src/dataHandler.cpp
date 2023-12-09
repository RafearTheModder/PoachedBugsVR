#include "dataHandler.h"

settingsStorage settings{};

void dataHandler::readSettings() {
	logger::info("reading settings");
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\PoachedBugsVR.ini"
	ini.LoadFile(SETTINGFILE_PATH);

	// (Relatively) safe fixes
	settings.reflectDamageLimitRemoval = ini.GetBoolValue("Fixes", "reflectDamageLimitRemoval", true);
	settings.improveAllEnchantmentEffects = ini.GetBoolValue("Fixes", "improveAllEnchantmentEffects", true);
	settings.perkEntrySpellCasterFix = ini.GetBoolValue("Fixes", "perkEntrySpellCasterFix", true);
	settings.powerAttacksStaminaRequirement = ini.GetBoolValue("Fixes", "powerAttacksStaminaRequirement", true);

	// Tweaks with extra dependence/compatibility concerns
	settings.poisonsUseOtherResistances = ini.GetBoolValue("Tweaks", "poisonsUseOtherResistances", false);
	settings.scrollsGrantExperience = ini.GetBoolValue("Tweaks", "scrollsGrantExperience", false);
	settings.stavesGrantExperience = ini.GetBoolValue("Tweaks", "stavesGrantExperience", false);
	settings.staffExperienceIgnoresEnchantmentCost = ini.GetBoolValue("Tweaks", "staffExperienceIgnoresEnchantmentCost", false);
	settings.perkEntryMultipleSpellsApplication = ini.GetBoolValue("Tweaks", "perkEntryMultipleSpellsApplication", false);
}
