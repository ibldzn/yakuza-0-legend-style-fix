#pragma once

#include <stdexcept>
#include <cstdint>

#define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace proxy
{
    void init();

    using ArcadeTestDLL_CanInsertCoin_t = bool(*)();
    extern ArcadeTestDLL_CanInsertCoin_t o_ArcadeTestDLL_CanInsertCoin;

    using ArcadeTestDLL_CanStartGame_t = bool(*)();
    extern ArcadeTestDLL_CanStartGame_t o_ArcadeTestDLL_CanStartGame;

    using ArcadeTestDLL_InitRom_t = bool(__fastcall*)(std::int64_t, std::int16_t*, std::uint16_t*, std::int64_t, bool, std::int64_t);
    extern ArcadeTestDLL_InitRom_t o_ArcadeTestDLL_InitRom;

    using ArcadeTestDLL_Shutdown_t = std::int64_t(*)();
    extern ArcadeTestDLL_Shutdown_t o_ArcadeTestDLL_Shutdown;

    using ArcadeTestDLL_Update_t = bool(__fastcall*)(std::int64_t, std::int64_t, std::int64_t*, std::int64_t);
    extern ArcadeTestDLL_Update_t o_ArcadeTestDLL_Update;
}