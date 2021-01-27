#include "hooks.h"

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
    static uintptr_t last_call = mem::ida_pattern_scan("B9 ? ? ? ? 66 85 48 08 74 68");
    uintptr_t return_address = reinterpret_cast<uintptr_t>(_ReturnAddress());

    std::int64_t ret = o_get_key_press(a1);

    // check if call was made from sub_140359E80
    // TODO: find a more proper way to check this
    if (return_address >= first_call && return_address <= last_call)
    {
        if (should_change_to_legend)
        {
            *reinterpret_cast<BYTE*>(ret + 0x9) = 0x1;
            should_change_to_legend = false;
        }
    }

    return ret;
}

std::int64_t __fastcall hooks::get_current_style::hook_func()
{
    static uintptr_t call_from_sub_140359E80 = mem::ida_pattern_scan("48 8D 4F 30 83 F8 03");
    std::int64_t ret = o_get_current_style();

    if (reinterpret_cast<uintptr_t>(_ReturnAddress()) == call_from_sub_140359E80)
    {
        static short index = []()
        {
            XINPUT_STATE dummy;
            for (short i = 0; i < 4; i++)
                if (XInputGetState(i, &dummy) == ERROR_SUCCESS)
                    return i;

            return static_cast<short>(-1);
        }();

        if (ret != 3)
        {
            if (GetAsyncKeyState(VK_TAB))
            {
                should_change_to_legend = true;
                ret = 3;
            }

            if (index != -1)
            {
                XINPUT_STATE state{};
                if (XInputGetState(index, &state) == ERROR_SUCCESS)
                {
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
                    {
                        should_change_to_legend = true;
                        ret = 3;
                    }
                }
            }
        }
        else
        {
            ret = -1;
        }
    }

    return ret;
}
