#include "QuickShotPerkFix.h"

#include "Addresses.h"

namespace Patch
{
    void QuickShotPerkFix::InstallPatch() {
        if(settings.poisonsUseOtherResistances)
        {
            REL::safe_write(RE::Address::QuickShot::GetBowPower.address(), reinterpret_cast<std::uintptr_t>(std::addressof(QuickShotPerkFix::GetBowPower)));

            logger::info("\"Quick draw perk fix\" patch installed!");
            logger::info(FMT_STRING("    Using quickDrawPerkSpeedMult = {}"), settings.quickDrawPerkSpeedMult);
        }
        else
        {
            logger::info("\"Quick draw perk fix\" patch is NOT enabled... skipping.");
        }
    };
    
    float QuickShotPerkFix::GetBowPower(float drawTime, float bowSpeed){
        double powerMult = 1.0;

        return powerMult;
    };
} // namespace Patch