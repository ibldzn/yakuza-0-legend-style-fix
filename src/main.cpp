#include "core/hooks.hpp"
#include "proxy/proxy.hpp"

#include <Windows.h>
#include <stdexcept>

DWORD WINAPI on_attach(LPVOID lp_param)
{
    try
    {
        proxy::init();
        hooks::init();
    }
    catch (const std::exception& ex)
    {
        MessageBoxA(nullptr, ex.what(), "ERROR!", MB_OK | MB_ICONERROR);
        FreeLibraryAndExitThread(static_cast<HMODULE>(lp_param), EXIT_FAILURE);
    }

#if defined(_DEBUG)
    while (!(GetAsyncKeyState(VK_END) & 0x8000))
        Sleep(50);

    FreeLibraryAndExitThread(static_cast<HMODULE>(lp_param), EXIT_SUCCESS);
#else
    return EXIT_SUCCESS;
#endif
}

BOOL WINAPI on_detach()
{
    hooks::destroy();
    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD call_reason, LPVOID)
{
    if (call_reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(h_module);
        if (HANDLE thread = CreateThread(nullptr, 0, on_attach, h_module, 0, nullptr))
        {
            CloseHandle(thread);
            return TRUE;
        }
    }
    else if (call_reason == DLL_PROCESS_DETACH)
    {
        return on_detach();
    }

    return FALSE;
}