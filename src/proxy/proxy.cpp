#include "proxy.hpp"

#include <Windows.h>
#include <stdexcept>
#include <string>

#if !defined(ASI_VER)
using CreateDXGIFactory_t = HRESULT (*)(REFIID riid, void** ppFactory);
static CreateDXGIFactory_t o_CreateDXGIFactory = nullptr;

using CreateDXGIFactory1_t = HRESULT (*)(REFIID riid, void** ppFactory);
static CreateDXGIFactory1_t o_CreateDXGIFactory1 = nullptr;

using CreateDXGIFactory2_t = HRESULT (*)(UINT Flags, REFIID riid, void** ppFactory);
static CreateDXGIFactory2_t o_CreateDXGIFactory2 = nullptr;

extern "C"
{
    __declspec(dllexport) HRESULT CreateDXGIFactory(REFIID riid, void** ppFactory)
    {
        return o_CreateDXGIFactory(riid, ppFactory);
    }

    __declspec(dllexport) HRESULT CreateDXGIFactory1(REFIID riid, void** ppFactory)
    {
        return o_CreateDXGIFactory1(riid, ppFactory);
    }

    __declspec(dllexport) HRESULT CreateDXGIFactory2(UINT Flag, REFIID riid, void** ppFactory)
    {
        return o_CreateDXGIFactory2(Flag, riid, ppFactory);
    }
}
#endif // !ASI_VER

void proxy::init()
{
#if !defined(ASI_VER)
    char system_path[MAX_PATH] {};
    if (!GetSystemDirectoryA(system_path, MAX_PATH))
        throw std::runtime_error("proxy::init - Failed to get system path!");

    std::string dxgi_path = std::string(system_path) + "\\dxgi.dll";
    HMODULE dxgi = LoadLibraryA(dxgi_path.c_str());
    if (!dxgi)
        throw std::runtime_error("proxy::init - Failed to load original dxgi.dll!");

    o_CreateDXGIFactory = reinterpret_cast<CreateDXGIFactory_t>(GetProcAddress(dxgi, "CreateDXGIFactory"));
    o_CreateDXGIFactory1 = reinterpret_cast<CreateDXGIFactory1_t>(GetProcAddress(dxgi, "CreateDXGIFactory1"));
    o_CreateDXGIFactory2 = reinterpret_cast<CreateDXGIFactory2_t>(GetProcAddress(dxgi, "CreateDXGIFactory2"));
#endif // !ASI_VER
}