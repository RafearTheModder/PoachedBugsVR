#pragma once

namespace Assembly{
    struct AbsoluteJumpAssembly
    {
        // jmp [addr]
        std::uint8_t  jmp = 0xFF;
        std::uint8_t  modrm = 0x25;
        std::int32_t  disp = 0x0;
        std::uint64_t addr;

        AbsoluteJumpAssembly(std::uintptr_t dst_addr){
            addr = dst_addr;
        }
    };
}