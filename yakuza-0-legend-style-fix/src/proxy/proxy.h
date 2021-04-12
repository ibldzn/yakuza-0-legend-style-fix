#pragma once

#define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

namespace proxy
{
    void init();

#ifndef Y0LSF_USE_ASI
    using CreateDXGIFactory_t = HRESULT(*)(REFIID riid, void** ppFactory);

    using CreateDXGIFactory1_t = HRESULT(*)(REFIID riid, void** ppFactory);

    using CreateDXGIFactory2_t = HRESULT(*)(UINT Flags, REFIID riid, void** ppFactory);
#endif // !Y0LSF_USE_ASI
}