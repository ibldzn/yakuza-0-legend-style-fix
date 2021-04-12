#pragma once

#include <cstdint>

namespace hooks
{
    void init();

    namespace get_key_press
    {
        using fn = std::int64_t(__fastcall*)(std::int64_t a1);
        std::int64_t __fastcall hook_func(std::int64_t a1);
    }

    namespace get_current_style
    {
        using fn = std::int64_t(__fastcall*)();
        std::int64_t __fastcall hook_func();
    }
}