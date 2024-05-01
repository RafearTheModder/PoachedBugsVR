# PoachedBugsVR
SKSE plugin providing a variety of bugfixes and tweaks for Skyrim VR.
Particular focus on reproducing fixes found in Scrambled Bugs for SE/AE that are commonly used across the "Simonrim" suite.

## Settings (in SKSE/plugins/PoachedBugsVR.ini)

Fixes (enabled by default, unless otherwise specified):
* improveAllEnchantmentEffects - Causes all effects in an enchantment to benefit from the players enchanting skill and perks, rather than only the costliest one
* perkEntrySpellCasterFix - Makes it so that the perk owner is recognized as the one who cast the spell on the target, rather than the target casting on themself
* powerAttacksStaminaRequirementNPC - Prevent NPCs from power attacking unless they have enough stamina for the full cost of the power attack. Makes frost magic and stamina draining poisons/spells more useful
* powerAttacksStaminaRequirementPlayer - (DOES NOT ACTUALLY WORK CURRENTLY. Will likely need to be implemented within Planck instead. Disabled here by default). Prevent the player from power attacking unless they have enough stamina for the full cost of the power attack
* resetHarvestFlags - Corrects an issue where various harvestable plants fail to correctly save the fact they have respawned, causing a save and reload to result in them suddenly being harvested again inexplicably

Tweaks (disabled by default, unless otherwise specified):
* poisonsUseOtherResistances - Poisons effects are resisted by their respective resist actor values, instead of always being resisted by poison resistance
* scrollsGrantExperience - Scrolls will grant experience when used, similar to actually casting their spell. Requires a mod to adjust scrolls to account for this (such as Mysticism)
* stavesGrantExperience - Staves will also grant experience similar to casting the spell they hold. Requires a mod to adjust scrolls to account for this (such as Mysticism)
* staffExperienceIgnoresEnchantmentCost - Stave experience gain is not effected by its enchantment cost. Recommended for use with Mysticism/Simonrim. Does nothing unless also using stavesGrantExperience
* perkEntryMultipleSpellsApplication - Allows multiple perk entry points to all simultaneously apply spells to their relevant targets, rather than only one being allowed. Will cause issues for mods that attempt to work around this limitation on their own.
* accumulateMagnitudeScaling - Makes accumulate magnitude type effects (such as wards) increase in maximum magnitude instead of accumulation rate when having their effectiveness increased by things such as dual casting or perk entry points
* reflectDamageLimitRemoval - (enabled by default) Removes the 100% cap on the reflect damage actor value

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CommonLibVR](https://github.com/RafearTheModder/CommonLibVR/tree/vr)
	* You need to build from the RafearTheModder/vr branch (will switch to alandtse/vr if and when changes are upstreamed)
	* Add this as as an environment variable `CommonLibVRPath`

## User Requirements
* [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
	* Needed for VR

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

### VR
```
cmake --preset vs2022-windows-vcpkg-vr
cmake --build buildvr --config Release
```
## License
[MIT](LICENSE)
