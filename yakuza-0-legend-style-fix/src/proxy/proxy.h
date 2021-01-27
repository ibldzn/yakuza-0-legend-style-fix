#pragma once

#include <stdexcept>
#include <string>
#include <cstdint>

#define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace proxy
{
    void init();

    using CreateDXGIFactory1_t = HRESULT(*)(REFIID riid, void** ppFactory);
    extern CreateDXGIFactory1_t o_CreateDXGIFactory1;

    using CreateDXGIFactory2_t = HRESULT(*)(UINT Flags, REFIID riid, void** ppFactory);
    extern CreateDXGIFactory2_t o_CreateDXGIFactory2;
}