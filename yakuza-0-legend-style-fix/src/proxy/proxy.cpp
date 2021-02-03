#include "proxy.h"

#ifndef PROXY_API
#  define PROXY_API extern "C" __declspec(dllexport)
#endif

static proxy::CreateDXGIFactory_t proxy::o_CreateDXGIFactory = nullptr;
static proxy::CreateDXGIFactory1_t proxy::o_CreateDXGIFactory1 = nullptr;
static proxy::CreateDXGIFactory2_t proxy::o_CreateDXGIFactory2 = nullptr;

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

    /* ::NOTE::
    * 
    * this is a bad practice (though it's very unlikely for this to be nullptr unless microsoft changed the name of the function which probably will never happen).
    * reason is CreateDXGIFactory2 only exist starting from Windows 8.1, making Windows 7 users unable to use this mod if I throw an exception here.
    * 
    * on my Windows 10 machine the game calls CreateDXGIFactory1 and CreateDXGIFactory2,
    * on issue 2 and 3 author's machine which running Windows 7 the game calls CreateDXGIFactory (and probably CreateDXGIFactory1 as well).
    * 
    * in other words all CreateDXGIFactory function is needed by the game,
    * but due to the non-existence of the CreateDXGIFactory2 function on Windows 7 I need to check Windows' version this mod is running on before throwing an exception,
    * but unfortunately using IsWindows8Point1OrGreater() from VersionHelpers api is not helping at all.
    * 
    * for the time being I'll leave it like this (I don't know when I will properly fix this, my school has been giving me tasks like there's no tomorrow ever since quarantine started).
    * 
    */

    // TODO: Proper null checking with windows version
    /*if (!proxy::o_CreateDXGIFactory2)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory2!");*/
}