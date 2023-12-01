#include "dataHandler.h"

void dataHandler::readSettings() {
	logger::info("reading settings");
	using namespace settings;
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\PoachedBugsVR.ini"
	ini.LoadFile(SETTINGFILE_PATH);

	reflectDamageLimitRemoval = ini.GetBoolValue("General", "reflectDamageLimitRemoval", true);
	scrollsGrantExperience = ini.GetBoolValue("General", "scrollsGrantExperience", true);
}

namespace settings
{
	bool reflectDamageLimitRemoval = true;
	bool scrollsGrantExperience = true;
}
