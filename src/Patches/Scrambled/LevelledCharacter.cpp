/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "LevelledCharacter.h"
#include "SKSE/Trampoline.h"

#include "Addresses.h"

namespace Patch
{
    void LevelledCharacter::InstallPatch() {
        if(settings.levelledCharacter)
        {
            SKSE::Trampoline& trampoline = SKSE::GetTrampoline();

            SKSE::AllocTrampoline(1 << 4);
            trampoline.write_branch<5>(RE::Address::LeveledCharacters::GetAllBelowForce.address(), GetAllBelowForce);

            logger::info("\"Levelled Character\" patch installed!");
        }
        else
        {
            logger::info("\"Levelled Character\" patch is NOT enabled... skipping.");
        }
    };
    
    std::uint32_t LevelledCharacter::GetAllBelowForce(RE::ExtraLevCreaModifier* extraLeveledCreatureModifier){
		switch (extraLeveledCreatureModifier->modifier.get())
		{
			case RE::LEV_CREA_MODIFIER::kEasy:
			{
				return 1; // lessThan
			}
			case RE::LEV_CREA_MODIFIER::kNone:
			{
				return 0; // equalTo
			}
			default:
			{
				return -1; // none
			}
		}
    };
} // namespace Patch