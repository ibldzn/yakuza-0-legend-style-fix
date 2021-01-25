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

PROXY_API char __fastcall ArcadeTestDLL_InitRom(__int64 a1, signed __int16* a2, unsigned __int16* a3, __int64 a4, char a5, __int64 a6)
{
	return proxy::o_ArcadeTestDLL_InitRom(a1, a2, a3, a4, a5, a6);
}

PROXY_API __int64 ArcadeTestDLL_Shutdown()
{
	return proxy::o_ArcadeTestDLL_Shutdown();
}

PROXY_API char __fastcall ArcadeTestDLL_Update(__int64 a1, __int64 a2, __int64* a3, __int64 a4)
{
	return proxy::o_ArcadeTestDLL_Update(a1, a2, a3, a4);
}

void proxy::init()
{
	HMODULE libtgsa = LoadLibraryA("libtgsa_o.dll");
	if (!libtgsa)
		throw std::runtime_error("Failed to load original libtgsa.dll!");

	proxy::o_ArcadeTestDLL_CanInsertCoin = reinterpret_cast<proxy::ArcadeTestDLL_CanInsertCoin_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_CanInsertCoin"));
	proxy::o_ArcadeTestDLL_CanStartGame = reinterpret_cast<proxy::ArcadeTestDLL_CanStartGame_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_CanStartGame"));
	proxy::o_ArcadeTestDLL_InitRom = reinterpret_cast<proxy::ArcadeTestDLL_InitRom_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_InitRom"));
	proxy::o_ArcadeTestDLL_Shutdown = reinterpret_cast<proxy::ArcadeTestDLL_Shutdown_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_Shutdown"));
	proxy::o_ArcadeTestDLL_Update = reinterpret_cast<proxy::ArcadeTestDLL_Update_t>(GetProcAddress(libtgsa, "ArcadeTestDLL_Update"));
}

#undef PROXY_API