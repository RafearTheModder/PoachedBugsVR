#pragma once

#include "RE/Skyrim.h"
#include "dataHandler.h"

namespace Patch
{
    class DrawnBowDetection
    {
    public:
        static void InstallPatch();
    private:

        inline static std::int32_t OnFrameUpdate(std::int64_t a1);
        static REL::Relocation<decltype(DrawnBowDetection::OnFrameUpdate)> originalOnFrameUpdate_;
    };
} // namespace Patch
