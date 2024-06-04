#include "DrawnBowDetection.h"

#include "Addresses.h"

namespace Patch
{
    void DrawnBowDetection::InstallPatch() {
        if(settings.drawnBowDetection)
        {
            // Update management stuff. Will eventually move this elsewhere for use across patches, but here will be fine for now.
            auto& trampoline = SKSE::GetTrampoline();
            SKSE::AllocTrampoline(1 << 4);
            originalOnFrameUpdate_ = trampoline.write_call<5>(RE::Address::OnFrameUpdate.address(), OnFrameUpdate);

            logger::info("\"Fix drawn bow detection\" patch installed!");
        }
        else
        {
            logger::info("\"Fix drawn bow detection\" patch is NOT enabled... skipping.");
        }
    };

    std::int32_t DrawnBowDetection::OnFrameUpdate(std::int64_t a1){
        auto player = RE::PlayerCharacter::GetSingleton();
		auto equippedWeapon = skyrim_cast<RE::TESObjectWEAP*>(player->GetEquippedObject(false));
        auto expectedAttackState = player->GetAttackState();

        //Override attackstate only in the event of the player drawing a bow.
        if (equippedWeapon ? (equippedWeapon->GetWeaponType() == RE::WEAPON_TYPE::kBow) : false)
        {
            // Here we use the fact an arrow is knocked and the distance it is pulled back to emulate the animation based attack states from flatrim.
            // We may need to also account for the bow release states at some point, but for now that will be left alone.
            if (player->bowState == RE::VR_Bow_State::kArrowKnocked)
            {
                if (player->currentBowDrawAmount >= settings.drawnBowSettings.completeThreshold)
                {
                    player->actorState1.meleeAttackState = RE::ATTACK_STATE_ENUM::kBowDrawn;
                    expectedAttackState = RE::ATTACK_STATE_ENUM::kBowDrawn;
                }
                else if (player->currentBowDrawAmount >= settings.drawnBowSettings.midThreshold)
                {
                    player->actorState1.meleeAttackState = RE::ATTACK_STATE_ENUM::kBowAttached;
                    expectedAttackState = RE::ATTACK_STATE_ENUM::kBowAttached;
                }
                else if(player->currentBowDrawAmount >= settings.drawnBowSettings.startThreshold)
                {
                    player->actorState1.meleeAttackState = RE::ATTACK_STATE_ENUM::kBowDraw;
                    expectedAttackState = RE::ATTACK_STATE_ENUM::kBowDraw;
                }
                else
                {
                    player->actorState1.meleeAttackState = RE::ATTACK_STATE_ENUM::kNone;
                    expectedAttackState = RE::ATTACK_STATE_ENUM::kNone;
                }
            }
        }

        auto retval = originalOnFrameUpdate_(a1);

        auto actualAttackState = player->GetAttackState();
        if (actualAttackState != expectedAttackState)
        {
            logger::info(FMT_STRING("{}: {} - Attack state override failed! actualAttackState = {}, expectedAttackState = {}"), __FILE__, std::to_string(__LINE__), std::to_string(std::to_underlying(actualAttackState)), std::to_string(std::to_underlying(expectedAttackState)));
        }

        return retval;
    };
    REL::Relocation<decltype(DrawnBowDetection::OnFrameUpdate)> DrawnBowDetection::originalOnFrameUpdate_{};
} // namespace Patch