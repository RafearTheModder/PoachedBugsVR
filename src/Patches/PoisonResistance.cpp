#include "PoisonResistance.h"

namespace Patch
{
    void PoisonResistance::InstallPatch() {
        if(settings.poisonsUseOtherResistances)
        {
            REL::Relocation<uintptr_t> actorMagicTargetVtableAddress{ REL::ID(260542) };
            auto actorCheckResistanceFuncPtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(actorMagicTargetVtableAddress.address())[0xA]));
            REL::safe_write(actorCheckResistanceFuncPtr, reinterpret_cast<std::uintptr_t>(std::addressof(PoisonResistance::CheckResistance)));
            REL::Relocation<uintptr_t> characterMagicTargetVtableAddress{ REL::ID(261401) };
            auto characterCheckResistanceFuncPtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(characterMagicTargetVtableAddress.address())[0xA]));
            REL::safe_write(characterCheckResistanceFuncPtr, reinterpret_cast<std::uintptr_t>(std::addressof(PoisonResistance::CheckResistance)));
            REL::Relocation<uintptr_t> playerMagicTargetVtableAddress{ REL::ID(261401) };
            auto playerCheckResistanceFuncPtr = reinterpret_cast<std::uintptr_t>(std::addressof(reinterpret_cast<std::uintptr_t*>(playerMagicTargetVtableAddress.address())[0xA]));
            REL::safe_write(playerCheckResistanceFuncPtr, reinterpret_cast<std::uintptr_t>(std::addressof(PoisonResistance::CheckResistance)));
            logger::info("Warning: \"Poison resistance\" patch is not implemented fully yet!");
        }
        else
        {
            logger::info("\"Poison resistance\" patch is NOT enabled... skipping.");
        }
    };
    
    float PoisonResistance::CheckResistance(RE::MagicTarget* a_magicTarget, RE::MagicItem* a_magicItem, RE::Effect* a_effect, RE::TESBoundObject* a_object){
        return 1.0;
    };
} // namespace Patch