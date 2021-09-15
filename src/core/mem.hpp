#pragma once

#include <string_view>

namespace mem
{
    uintptr_t pattern_scan(std::string_view module_name, std::string_view pattern);
    uintptr_t follow_rel32(uintptr_t address, ptrdiff_t offset = 0x1);
}