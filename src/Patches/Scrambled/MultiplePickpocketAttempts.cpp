/*
    WARNING: This file is NOT MIT licensed! It is adapted from Scrambled Bugs under non-transferable permission from KernalsEgg.
             See the license section of README.md for further explanation.
*/

#include "MultiplePickpocketAttempts.h"

#include "Addresses.h"

namespace Patch
{
    void MultiplePickpocketAttempts::InstallPatch() {
        if(settings.multiplePickpocketAttempts)
        {
            REL::safe_write(RE::Address::MultiplePickpocketAttempts::AttackOnSight.address(), REL::NOP2, 2);
            REL::safe_write(RE::Address::MultiplePickpocketAttempts::HasBeenPickpocketed.address(), REL::NOP2, 2);

            logger::info("\"Multiple Pickpocket Attempts\" patch installed!");
        }
        else
        {
            logger::info("\"Multiple Pickpocket Attempts\" patch is NOT enabled... skipping.");
        }
    };
} // namespace Patch