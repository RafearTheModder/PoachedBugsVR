#pragma once
class dataHandler
{

public:

	static void readSettings();
};

struct settingsStorage
{
	bool reflectDamageLimitRemoval=true;
	bool scrollsGrantExperience=true;
	bool poisonsUseOtherResistances=true;
	bool stavesGrantExperience=true;
	bool staffExperienceIgnoresEnchantmentCost=true;
	bool improveAllEnchantmentEffects=true;
};

extern settingsStorage settings;