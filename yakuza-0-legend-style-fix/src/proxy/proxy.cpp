#include "proxy.h"

#ifndef PROXY_API
#  define PROXY_API extern "C" __declspec(dllexport)
#endif

static proxy::CreateDXGIFactory1_t proxy::o_CreateDXGIFactory1 = nullptr;
static proxy::CreateDXGIFactory2_t proxy::o_CreateDXGIFactory2 = nullptr;

PROXY_API HRESULT CreateDXGIFactory1(REFIID riid, void** ppFactory)
{
    return proxy::o_CreateDXGIFactory1(riid, ppFactory);
}

PROXY_API HRESULT CreateDXGIFactory2(UINT Flag, REFIID riid, void** ppFactory)
{
    return proxy::o_CreateDXGIFactory2(Flag, riid, ppFactory);
}

#undef PROXY_API

void proxy::init()
{
    char system_path[MAX_PATH]{};
    if (GetSystemDirectoryA(system_path, MAX_PATH) == NULL)
        throw std::runtime_error("proxy::init - Failed to get system path!");

    std::string dxgi_path = std::string(system_path) + "\\dxgi.dll";
    HMODULE dxgi = LoadLibraryA(dxgi_path.c_str());
    if (!dxgi)
        throw std::runtime_error("proxy::init - Failed to load original dxgi.dll!");

    proxy::o_CreateDXGIFactory1 = reinterpret_cast<proxy::CreateDXGIFactory1_t>(GetProcAddress(dxgi, "CreateDXGIFactory1"));
    if (!proxy::o_CreateDXGIFactory1)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory1!");

    proxy::o_CreateDXGIFactory2 = reinterpret_cast<proxy::CreateDXGIFactory2_t>(GetProcAddress(dxgi, "CreateDXGIFactory2"));
    if (!proxy::o_CreateDXGIFactory2)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory2!");
}