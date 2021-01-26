#include "proxy.h"

#ifndef PROXY_API
#  define PROXY_API extern "C" __declspec(dllexport)
#endif

static proxy::ArcadeTestDLL_CanInsertCoin_t proxy::o_ArcadeTestDLL_CanInsertCoin = nullptr;
static proxy::ArcadeTestDLL_CanStartGame_t	proxy::o_ArcadeTestDLL_CanStartGame = nullptr;
static proxy::ArcadeTestDLL_InitRom_t		proxy::o_ArcadeTestDLL_InitRom = nullptr;
static proxy::ArcadeTestDLL_Shutdown_t		proxy::o_ArcadeTestDLL_Shutdown = nullptr;
static proxy::ArcadeTestDLL_Update_t		proxy::o_ArcadeTestDLL_Update = nullptr;

PROXY_API bool ArcadeTestDLL_CanInsertCoin()
{
    return proxy::o_ArcadeTestDLL_CanInsertCoin();
}

PROXY_API bool ArcadeTestDLL_CanStartGame()
{
    return proxy::o_ArcadeTestDLL_CanStartGame();
}

PROXY_API bool __fastcall ArcadeTestDLL_InitRom(std::int64_t a1, std::int16_t* a2, std::uint16_t* a3, std::int64_t a4, bool a5, std::int64_t a6)
{
    return proxy::o_ArcadeTestDLL_InitRom(a1, a2, a3, a4, a5, a6);
}

PROXY_API std::int64_t ArcadeTestDLL_Shutdown()
{
    return proxy::o_ArcadeTestDLL_Shutdown();
}

PROXY_API bool __fastcall ArcadeTestDLL_Update(std::int64_t a1, std::int64_t a2, std::int64_t* a3, std::int64_t a4)
{
    return proxy::o_ArcadeTestDLL_Update(a1, a2, a3, a4);
}

void proxy::init()
{
    HMODULE libtgsa = LoadLibraryA("libtgsa_o.dll");
    if (!libtgsa)
        throw std::runtime_error("proxy::init - Failed to load original libtgsa.dll!");

    proxy::o_ArcadeTestDLL_CanInsertCoin = reinterpret_cast<proxy::ArcadeTestDLL_CanInsertCoin_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_CanInsertCoin"));
    if (!proxy::o_ArcadeTestDLL_CanInsertCoin)
        throw std::runtime_error("proxy::init - Failed to get function address for ArcadeTestDLL_CanInsertCoin!");

    proxy::o_ArcadeTestDLL_CanStartGame = reinterpret_cast<proxy::ArcadeTestDLL_CanStartGame_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_CanStartGame"));
    if (!proxy::o_ArcadeTestDLL_CanStartGame)
        throw std::runtime_error("proxy::init - Failed to get function address for ArcadeTestDLL_CanStartGame!");

    proxy::o_ArcadeTestDLL_InitRom = reinterpret_cast<proxy::ArcadeTestDLL_InitRom_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_InitRom"));
    if (!proxy::o_ArcadeTestDLL_InitRom)
        throw std::runtime_error("proxy::init - Failed to get function address for ArcadeTestDLL_InitRom!");

    proxy::o_ArcadeTestDLL_Shutdown = reinterpret_cast<proxy::ArcadeTestDLL_Shutdown_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_Shutdown"));
    if (!proxy::o_ArcadeTestDLL_Shutdown)
        throw std::runtime_error("proxy::init - Failed to get function address for ArcadeTestDLL_Shutdown!");

    proxy::o_ArcadeTestDLL_Update = reinterpret_cast<proxy::ArcadeTestDLL_Update_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_Update"));
    if (!proxy::o_ArcadeTestDLL_Update)
        throw std::runtime_error("proxy::init - Failed to get function address for ArcadeTestDLL_Update!");
}

#undef PROXY_API