# PoachedBugsVR
SKSE plugin providing a variety of bugfixes and tweaks for Skyrim VR.
Particular focus on reproducing fixes found in Scrambled Bugs for SE/AE that are commonly used across the "Simonrim" suite.

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CommonLibVR](https://github.com/alandtse/CommonLibVR/tree/vr)
	* You need to build from the alandtse/vr branch
	* Add this as as an environment variable `CommonLibVRPath` instead of /extern

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
