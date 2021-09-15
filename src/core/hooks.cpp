#include "hooks.hpp"

#include "mem.hpp"

#include <stdexcept>
#include <MinHook.h>
#include <intrin.h>

using get_key_press_t = int64_t(__fastcall*)(uintptr_t);
static int64_t __fastcall hk_get_key_press(uintptr_t);
static get_key_press_t o_get_key_press = nullptr;

using get_current_style_t = int32_t(__fastcall*)();
static int32_t __fastcall hk_get_current_style();
static get_current_style_t o_get_current_style = nullptr;

static bool should_change_to_legend = false;
static bool was_right_analog_pressed = false;

void hooks::init()
{
    if (MH_Initialize() != MH_OK)
        throw std::runtime_error("hooks::init - Failed to initialize minhook!");

    uintptr_t get_key_press = mem::follow_rel32(mem::pattern_scan("yakuza0.exe", "E8 ? ? ? ? F3 0F 59 30"));
    if (MH_CreateHook(reinterpret_cast<void*>(get_key_press), hk_get_key_press,
                      reinterpret_cast<void**>(&o_get_key_press)) != MH_OK)
        throw std::runtime_error("hooks::init - Failed to hook get key press!");

    uintptr_t get_current_style = mem::follow_rel32(mem::pattern_scan("yakuza0.exe", "E8 ? ? ? ? 3B D8 75 0A"));
    if (MH_CreateHook(reinterpret_cast<void*>(get_current_style), hk_get_current_style,
                      reinterpret_cast<void**>(&o_get_current_style)) != MH_OK)
        throw std::runtime_error("hooks::init - Failed to hook get current style!");

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        throw std::runtime_error("hooks::init - Failed to enable hooks!");
}

void hooks::destroy()
{
    MH_Uninitialize();
}

static int64_t __fastcall hk_get_key_press(uintptr_t rcx)
{
    static uintptr_t first_call = mem::pattern_scan("yakuza0.exe", "F6 40 09 01 0F 84 ? ? ? ?");
    static uintptr_t last_call = mem::pattern_scan("yakuza0.exe", "B9 ? ? ? ? 66 85 48 08 74 68");

    int64_t key_state = o_get_key_press(rcx);

    if (uintptr_t ret_addr = reinterpret_cast<uintptr_t>(_ReturnAddress()); ret_addr >= first_call && ret_addr <= last_call)
    {
        was_right_analog_pressed = *reinterpret_cast<uint8_t*>(key_state + 11) == 16;

        if (should_change_to_legend)
        {
            *reinterpret_cast<uint8_t*>(key_state + 9) |= 1;
            should_change_to_legend = false;
        }
    }

    return key_state;
}

static int32_t __fastcall hk_get_current_style()
{
    static uintptr_t call_from_sub_140359E80 = mem::pattern_scan("yakuza0.exe", "48 8D 4F 30 83 F8 03");
    int32_t style = o_get_current_style();

    if (reinterpret_cast<uintptr_t>(_ReturnAddress()) != call_from_sub_140359E80)
        return style;

    // https://i.imgur.com/qJFcBIv.png
    // the goal is to prevent the game from executing line 31
    if (style == 3)
        return -1;

    if (was_right_analog_pressed || (GetAsyncKeyState(VK_TAB) & 0x8000))
    {
        should_change_to_legend = true;
        return 3;
    }

    return style;
}