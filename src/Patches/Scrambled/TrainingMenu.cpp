/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "Patches/Scrambled/TrainingMenu.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
	void TrainingMenu::InstallPatch()
	{
		if(settings.trainingMenu){
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

			REL::safe_write(RE::Address::TrainingMenu::GetPermanentActorValue.address()+0x2, 0x18ui8);

			logger::info("\"TrainingMenu\" patch installed!");
		}
		else{
            logger::info("\"TrainingMenu\" patch is NOT enabled... skipping.");
		}
	}
}
