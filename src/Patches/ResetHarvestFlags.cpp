#include "ResetHarvestFlags.h"

#include "Addresses.h"

namespace Patch
{
    void ResetHarvestFlags::InstallPatch() {
        if(settings.resetHarvestFlags)
        {
            logger::info("\"Reset harvest flags\" patch installed!");
        }
        else
        {
            logger::info("\"Reset harvest flags\" patch is NOT enabled... skipping.");
        }
    };

    void ResetHarvestFlags::SetEmpty(RE::TESObjectREFR* object, bool empty){
        if ((object->GetBaseObject()->Is(RE::FormType::Tree))||\
            (object->GetBaseObject()->Is(RE::FormType::Flora)))
        {
            object->RemoveChange(RE::TESObjectREFR::ChangeFlags::kEmpty);
        }
        
        originalSetEmpty(object, empty);
    };
    
    REL::Relocation<decltype(ResetHarvestFlags::SetEmpty)> ResetHarvestFlags::originalSetEmpty;
} // namespace Patch