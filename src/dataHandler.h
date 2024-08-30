#pragma once
class dataHandler
{

public:

	static void readSettings();
};

struct drawnBowAdvancedSettings
{
	double startThreshold = 0.20;
	double midThreshold = 0.4;
	double completeThreshold = 0.8;
};

struct DifficultyMultipliers
{
	bool commandedActors = false;
	bool teammates = false;
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
	bool drawnBowDetection=true;
	bool resetHarvestFlags=true;
	bool levelledCharacter=false;
	bool weaponCharge=true;
	bool enchantmentCost=true;
	bool actorValuePercentage=true;
	bool armorWeightModPerkEntry=true;
	bool trainingMenu=true;
	DifficultyMultipliers difficultyMultipliers;

	drawnBowAdvancedSettings drawnBowSettings;
};

extern settingsStorage settings;