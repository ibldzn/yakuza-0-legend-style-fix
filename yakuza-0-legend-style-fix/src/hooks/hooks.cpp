#include <stdexcept>
#include <intrin.h>

#define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#undef WIN32_LEAN_AND_MEAN

#include <Xinput.h>

#include "hooks.h"
#include "../mem/mem.h"

static hooks::get_key_press::fn o_get_key_press = nullptr;
static hooks::get_current_style::fn o_get_current_style = nullptr;

static bool should_change_to_legend = false;

void hooks::init()
{
    uintptr_t hook_at = mem::follow(mem::ida_pattern_scan("E8 ? ? ? ? F3 0F 59 30"));
    if (!mem::hook(hook_at, hooks::get_key_press::hook_func, &o_get_key_press))
        throw std::runtime_error("hooks::init - Failed to hook get_key_press function!");

    hook_at = mem::follow(mem::ida_pattern_scan("E8 ? ? ? ? 3B D8 75 0A"));
    if (!mem::hook(hook_at, hooks::get_current_style::hook_func, &o_get_current_style))
        throw std::runtime_error("hooks::init - Failed to hook get_current_style function!");
}

std::int64_t __fastcall hooks::get_key_press::hook_func(std::int64_t a1)
{
    static uintptr_t first_call = mem::ida_pattern_scan("F6 40 09 01 0F 84 ? ? ? ?");
    std::int64_t ret = o_get_key_press(a1);

    if (reinterpret_cast<uintptr_t>(_ReturnAddress()) == first_call &&
        should_change_to_legend)
    {
        *reinterpret_cast<BYTE*>(ret + 0x9) = 0x1;
        should_change_to_legend = false;
    }

    return ret;
}

std::int64_t __fastcall hooks::get_current_style::hook_func()
{
    static uintptr_t call_from_sub_140359E80 = mem::ida_pattern_scan("48 8D 4F 30 83 F8 03");
    std::int64_t cur_style = o_get_current_style();

    if (reinterpret_cast<uintptr_t>(_ReturnAddress()) != call_from_sub_140359E80)
        return cur_style;

    static short index = []()
    {
        XINPUT_STATE dummy{};
        for (short i = 0; i < 4; i++)
            if (XInputGetState(i, &dummy) == ERROR_SUCCESS)
                return i;

        return static_cast<short>(-1);
    }();

    if (cur_style != 3) // !LEGEND
    {
        if (GetAsyncKeyState(VK_TAB) & 0x8000)
        {
            should_change_to_legend = true;
            return 3;
        }

        if (index != -1)
        {
            XINPUT_STATE state{};
            if (XInputGetState(index, &state) != ERROR_SUCCESS)
                return cur_style;

            if (!(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB))
                return cur_style;
            
            should_change_to_legend = true;
            return 3;
        }
    }
    
    return -1;
}
