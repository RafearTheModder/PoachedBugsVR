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
};

extern settingsStorage settings;