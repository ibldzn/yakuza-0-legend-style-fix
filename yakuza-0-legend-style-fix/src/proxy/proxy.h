#include <Windows.h>
#include <stdexcept>

namespace proxy 
{
	void init();

	using ArcadeTestDLL_CanInsertCoin_t = bool(*)();
	extern ArcadeTestDLL_CanInsertCoin_t o_ArcadeTestDLL_CanInsertCoin;

	using ArcadeTestDLL_CanStartGame_t = bool(*)();
	extern ArcadeTestDLL_CanStartGame_t o_ArcadeTestDLL_CanStartGame;

	using ArcadeTestDLL_InitRom_t = char(__fastcall*)(__int64, signed __int16*, unsigned __int16*, __int64, char, __int64);
	extern ArcadeTestDLL_InitRom_t o_ArcadeTestDLL_InitRom;

	using ArcadeTestDLL_Shutdown_t = __int64(*)();
	extern ArcadeTestDLL_Shutdown_t o_ArcadeTestDLL_Shutdown;

	using ArcadeTestDLL_Update_t = char(__fastcall*)(__int64, __int64, __int64*, __int64);
	extern ArcadeTestDLL_Update_t o_ArcadeTestDLL_Update;
}