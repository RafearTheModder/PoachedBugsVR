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
	bool perkEntryMultipleSpellsApplication=true;
	bool perkEntrySpellCasterFix=true;
	bool powerAttacksStaminaRequirementNPC=true;
	bool powerAttacksStaminaRequirementPlayer=false;
	bool accumulateMagnitudeScaling=false;
};

extern settingsStorage settings;