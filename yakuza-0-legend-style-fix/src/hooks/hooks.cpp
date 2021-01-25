#include "hooks.h"

static hooks::change_style::fn o_change_style = nullptr;
static hooks::sub_1409ADDB0::fn o_sub_1409ADDB0 = nullptr;

void hooks::init()
{
    auto hook_at = mem::follow(mem::ida_pattern_scan("E8 ? ? ? ? 89 B7 ? ? ? ? FF 87 ? ? ? ?"));
    if (!mem::hook(hook_at, hooks::change_style::hook_func, &o_change_style))
        throw std::runtime_error("Failed to hook change_style function!");

    hook_at = mem::follow(mem::ida_pattern_scan("E8 ? ? ? ? 48 83 BF ? ? ? ? ? 74 3F"));
    if (!mem::hook(hook_at, hooks::sub_1409ADDB0::hook_func, &o_sub_1409ADDB0))
        throw std::runtime_error("Failed to hook sub_1409ADDB0!");
}

__int64 __fastcall hooks::change_style::hook_func(unsigned __int64 is_majima, int style)
{
    static uintptr_t change_style_from_pause_menu = mem::ida_pattern_scan("E8 ? ? ? ? 85 C0 75 2B 48 8B 0D ? ? ? ? 48");
    if (reinterpret_cast<uintptr_t>(_ReturnAddress()) == change_style_from_pause_menu)
        return o_change_style(is_majima, style);

    static short index = []()
    {
        XINPUT_STATE dummy;
        for (short i = 0; i < 4; i++)
            if (XInputGetState(i, &dummy) == ERROR_SUCCESS)
                return i;

        return static_cast<short>(-1);
    }();

    if (index != -1)
    {
        XINPUT_STATE state;
        if (XInputGetState(index, &state) == ERROR_SUCCESS)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
                style = 3;
        }
    }
    
    if (GetAsyncKeyState(VK_TAB))
        style = 3;

    return o_change_style(is_majima, style);
}

__int64 __fastcall hooks::sub_1409ADDB0::hook_func(__int64 a1)
{
    // if you pressed the same key as your current style or 
    // pressed any dpad button while using legend style
    // this is the return address
    static uintptr_t addr = mem::ida_pattern_scan("8B D0 44 8B C7 E8 ? ? ? ? 48 8D 05 ? ? ? ?") + 0xA;
    if (reinterpret_cast<uintptr_t>(_ReturnAddress()) != addr)
        return o_sub_1409ADDB0(a1);

    using is_majima_t = signed __int64(*)();
    static auto is_majima_fn = reinterpret_cast<is_majima_t>(mem::follow(mem::ida_pattern_scan("E8 ? ? ? ? 8D 50 06")));
    auto is_majima = is_majima_fn();

    using get_current_style_t = signed __int64(*)();
    static auto get_current_style = reinterpret_cast<get_current_style_t>(mem::follow(mem::ida_pattern_scan("E8 ? ? ? ? 3B D8 75 0A")));
    auto current_style = get_current_style();

    static short index = []()
    {
        XINPUT_STATE dummy;
        for (short i = 0; i < 4; i++)
            if (XInputGetState(i, &dummy) == ERROR_SUCCESS)
                return i;

        return static_cast<short>(-1);
    }();

    if (index != -1)
    {
        XINPUT_STATE state;
        if (XInputGetState(index, &state) == ERROR_SUCCESS)
        {
            if (current_style == 3) // current_style == legend
            {
                if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
                    hooks::change_style::hook_func(is_majima, 0);

                else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
                    hooks::change_style::hook_func(is_majima, 1);

                else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
                    hooks::change_style::hook_func(is_majima, 2);
            }
        }
    }

    return o_sub_1409ADDB0(a1);
}
