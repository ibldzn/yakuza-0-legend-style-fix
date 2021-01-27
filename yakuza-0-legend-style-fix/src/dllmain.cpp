#include <stdexcept>

#define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

#include "proxy/proxy.h"
#include "mem/mem.h"
#include "hooks/hooks.h"

DWORD WINAPI on_attach(LPVOID lp_param)
{
    try
    {
        proxy::init();
        mem::init();
        hooks::init();
    }
    catch (const std::exception& ex)
    {
        MessageBoxA(NULL, ex.what(), "ERROR!", MB_OK | MB_ICONERROR);
        FreeLibraryAndExitThread(static_cast<HMODULE>(lp_param), EXIT_FAILURE);
    }

    while (!(GetAsyncKeyState(VK_END) & 0x8000))
        Sleep(200);

    FreeLibraryAndExitThread(static_cast<HMODULE>(lp_param), EXIT_SUCCESS);
}

BOOL WINAPI on_detach()
{
    mem::destroy();
    return TRUE;
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD dw_reason, LPVOID lp_reserved)
{
    if (dw_reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(h_module);
        if (HANDLE thread = CreateThread(nullptr, NULL, on_attach, nullptr, NULL, nullptr))
            CloseHandle(thread);
    }
    else if (dw_reason == DLL_PROCESS_DETACH)
    {
        return on_detach();
    }

    return TRUE;
}