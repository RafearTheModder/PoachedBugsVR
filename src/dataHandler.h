#pragma once
class dataHandler
{

public:

	static void readSettings();
};

namespace settings 
{
	extern bool reflectDamageLimitRemoval;
	extern bool scrollsGrantExperience;
}