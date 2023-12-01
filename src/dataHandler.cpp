#include "dataHandler.h"

settingsStorage settings{};

void dataHandler::readSettings() {
	logger::info("reading settings");
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\PoachedBugsVR.ini"
	ini.LoadFile(SETTINGFILE_PATH);

	settings.reflectDamageLimitRemoval = ini.GetBoolValue("General", "reflectDamageLimitRemoval", true);
	settings.scrollsGrantExperience = ini.GetBoolValue("General", "scrollsGrantExperience", true);
	settings.poisonsUseOtherResistances = ini.GetBoolValue("General", "poisonsUseOtherResistances", true);
	settings.scrollsGrantExperience = ini.GetBoolValue("General", "stavesGrantExperience", true);
	settings.staffExperienceIgnoresEnchantmentCost = ini.GetBoolValue("General", "staffExperienceIgnoresEnchantmentCost", true);
}
