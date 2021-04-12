#pragma once

#include "../../deps/minhook/include/MinHook.h"

namespace mem
{
    void init();
    bool destroy();

    template <typename T>
    bool hook(uintptr_t target, LPVOID detour, T** p_original_func = NULL)
    {
        if (MH_CreateHook(reinterpret_cast<LPVOID>(target), detour, reinterpret_cast<LPVOID*>(p_original_func)) != MH_OK)
            return false;

        if (MH_EnableHook(reinterpret_cast<LPVOID>(target)) != MH_OK)
            return false;

        return true;
    }

    uintptr_t ida_pattern_scan(const char* pattern);
    uintptr_t follow(uintptr_t base, uintptr_t offset = 0x1);
}