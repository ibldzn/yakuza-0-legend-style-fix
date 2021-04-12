#include <stdexcept>
#include <string>

#include "proxy.h"

#ifndef Y0LSF_USE_ASI

    static proxy::CreateDXGIFactory_t o_CreateDXGIFactory = nullptr;
    static proxy::CreateDXGIFactory1_t o_CreateDXGIFactory1 = nullptr;
    static proxy::CreateDXGIFactory2_t o_CreateDXGIFactory2 = nullptr;

# define Y0LSF_API extern "C" __declspec(dllexport)

    Y0LSF_API HRESULT CreateDXGIFactory(REFIID riid, void** ppFactory)
    {
        return o_CreateDXGIFactory(riid, ppFactory);
    }

    Y0LSF_API HRESULT CreateDXGIFactory1(REFIID riid, void** ppFactory)
    {
        return o_CreateDXGIFactory1(riid, ppFactory);
    }

    Y0LSF_API HRESULT CreateDXGIFactory2(UINT Flag, REFIID riid, void** ppFactory)
    {
        return o_CreateDXGIFactory2(Flag, riid, ppFactory);
    }

# undef Y0LSF_API

#endif // !Y0LSF_USE_ASI

void proxy::init()
{
#ifndef Y0LSF_USE_ASI
    wchar_t system_path[MAX_PATH]{};
    if (GetSystemDirectory(system_path, MAX_PATH) == NULL)
        throw std::runtime_error("proxy::init - Failed to get system path!");

    std::wstring dxgi_path = std::wstring(system_path) + L"\\dxgi.dll";
    HMODULE dxgi = LoadLibrary(dxgi_path.c_str());
    if (!dxgi)
        throw std::runtime_error("proxy::init - Failed to load original dxgi.dll!");

    o_CreateDXGIFactory = reinterpret_cast<proxy::CreateDXGIFactory_t>(GetProcAddress(dxgi, "CreateDXGIFactory"));
    if (!o_CreateDXGIFactory)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory!");

    o_CreateDXGIFactory1 = reinterpret_cast<proxy::CreateDXGIFactory1_t>(GetProcAddress(dxgi, "CreateDXGIFactory1"));
    if (!o_CreateDXGIFactory1)
        throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory1!");

    o_CreateDXGIFactory2 = reinterpret_cast<proxy::CreateDXGIFactory2_t>(GetProcAddress(dxgi, "CreateDXGIFactory2"));
    if (!o_CreateDXGIFactory2)
    {
        bool is_windows8dot1_or_higher = []()
        {
            bool ret = false;
            HMODULE ntdll = GetModuleHandle(L"ntdll.dll");

            if (ntdll)
            {
                using RtlGetVersion_t = LONG(*)(LPOSVERSIONINFOEXW);
                RtlGetVersion_t RtlGetVersion = reinterpret_cast<RtlGetVersion_t>(GetProcAddress(ntdll, "RtlGetVersion"));

                if (RtlGetVersion)
                {
                    OSVERSIONINFOEXW os_info{};
                    os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
                    RtlGetVersion(&os_info);

                    ret = (os_info.dwMajorVersion >= 6 && os_info.dwMinorVersion >= 3) || os_info.dwMajorVersion >= 10;
                }
            }

            return ret;
        }();

        if (is_windows8dot1_or_higher)
            throw std::runtime_error("proxy::init - Failed to get address for CreateDXGIFactory2!");
    }
#endif // !Y0LSF_USE_ASI
}