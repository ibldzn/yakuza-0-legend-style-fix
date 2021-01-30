#include "proxy.h"

#ifndef PROXY_API
#  define PROXY_API extern "C" __declspec(dllexport)
#endif

static proxy::CreateDXGIFactory_t proxy::o_CreateDXGIFactory = nullptr;
static proxy::CreateDXGIFactory1_t proxy::o_CreateDXGIFactory1 = nullptr;
static proxy::CreateDXGIFactory2_t proxy::o_CreateDXGIFactory2 = nullptr;
static proxy::DXGIDeclareAdapterRemovalSupport_t proxy::o_DXGIDeclareAdapterRemovalSupport = nullptr;
static proxy::DXGIGetDebugInterface1_t proxy::o_DXGIGetDebugInterface1 = nullptr;

PROXY_API HRESULT CreateDXGIFactory(REFIID riid, void** ppFactory)
{
    return proxy::o_CreateDXGIFactory(riid, ppFactory);
}

PROXY_API HRESULT CreateDXGIFactory1(REFIID riid, void** ppFactory)
{
    return proxy::o_CreateDXGIFactory1(riid, ppFactory);
}

PROXY_API HRESULT CreateDXGIFactory2(UINT Flag, REFIID riid, void** ppFactory)
{
    return proxy::o_CreateDXGIFactory2(Flag, riid, ppFactory);
}

PROXY_API HRESULT DXGIDeclareAdapterRemovalSupport()
{
    return proxy::o_DXGIDeclareAdapterRemovalSupport();
}

PROXY_API HRESULT DXGIGetDebugInterface1(UINT Flags, REFIID riid, void** pDebug)
{
    return proxy::o_DXGIGetDebugInterface1(Flags, riid, pDebug);
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

    proxy::o_CreateDXGIFactory = reinterpret_cast<proxy::CreateDXGIFactory_t>(GetProcAddress(dxgi, "CreateDXGIFactory"));
    if (!proxy::o_CreateDXGIFactory)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory!");

    proxy::o_CreateDXGIFactory1 = reinterpret_cast<proxy::CreateDXGIFactory1_t>(GetProcAddress(dxgi, "CreateDXGIFactory1"));
    if (!proxy::o_CreateDXGIFactory1)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory1!");

    proxy::o_CreateDXGIFactory2 = reinterpret_cast<proxy::CreateDXGIFactory2_t>(GetProcAddress(dxgi, "CreateDXGIFactory2"));
    if (!proxy::o_CreateDXGIFactory2)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory2!");

    proxy::o_DXGIDeclareAdapterRemovalSupport = reinterpret_cast<proxy::DXGIDeclareAdapterRemovalSupport_t>(GetProcAddress(dxgi, "DXGIDeclareAdapterRemovalSupport"));
    if (!proxy::o_DXGIDeclareAdapterRemovalSupport)
        throw std::runtime_error("proxy::init - Failed to get address for DXGIDeclareAdapterRemovalSupport!");

    proxy::o_DXGIGetDebugInterface1 = reinterpret_cast<proxy::DXGIGetDebugInterface1_t>(GetProcAddress(dxgi, "DXGIGetDebugInterface1"));
    if (!proxy::o_DXGIGetDebugInterface1)
        throw std::runtime_error("proxy::init - Failed to get address for DXGIGetDebugInterface1!");
}