/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "LevelledCharacter.h"

#include "Addresses.h"
#include "Utilities/Assembly.h"

namespace Patch
{
    void LevelledCharacter::InstallPatch() {
        if(settings.levelledCharacter)
        {
            auto GetAllBelowForceJmp = Assembly::AbsoluteJumpAssembly(reinterpret_cast<std::uintptr_t>(std::addressof(LevelledCharacter::GetAllBelowForce)));
            REL::safe_write(RE::Address::LeveledCharacters::GetAllBelowForce.address(), &GetAllBelowForceJmp, sizeof(GetAllBelowForceJmp));

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