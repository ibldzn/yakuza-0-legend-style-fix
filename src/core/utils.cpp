#include "utils.hpp"

#include <Windows.h>
#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <string_view>

static int get_keycode(std::string_view key_name)
{
    struct Keycode {
        std::string_view name;
        int key;
    };

#define MAKE_KC(kc) \
  Keycode           \
  {                 \
#    kc, kc         \
  }

#define MAKE_CUSTOM_KC(kc_str, kc_code) \
  Keycode                               \
  {                                     \
    kc_str, kc_code                     \
  }

    static constexpr std::array KEYCODES = {
        MAKE_KC(VK_LBUTTON),
        MAKE_KC(VK_RBUTTON),
        MAKE_KC(VK_CANCEL),
        MAKE_KC(VK_MBUTTON),
        MAKE_KC(VK_XBUTTON1),
        MAKE_KC(VK_XBUTTON2),
        MAKE_KC(VK_BACK),
        MAKE_KC(VK_TAB),
        MAKE_KC(VK_CLEAR),
        MAKE_KC(VK_RETURN),
        MAKE_KC(VK_SHIFT),
        MAKE_KC(VK_CONTROL),
        MAKE_KC(VK_MENU),
        MAKE_KC(VK_PAUSE),
        MAKE_KC(VK_CAPITAL),
        MAKE_KC(VK_KANA),
        MAKE_KC(VK_HANGUL),
        MAKE_KC(VK_IME_ON),
        MAKE_KC(VK_JUNJA),
        MAKE_KC(VK_FINAL),
        MAKE_KC(VK_HANJA),
        MAKE_KC(VK_KANJI),
        MAKE_KC(VK_IME_OFF),
        MAKE_KC(VK_ESCAPE),
        MAKE_KC(VK_CONVERT),
        MAKE_KC(VK_NONCONVERT),
        MAKE_KC(VK_ACCEPT),
        MAKE_KC(VK_MODECHANGE),
        MAKE_KC(VK_SPACE),
        MAKE_KC(VK_PRIOR),
        MAKE_KC(VK_NEXT),
        MAKE_KC(VK_END),
        MAKE_KC(VK_HOME),
        MAKE_KC(VK_LEFT),
        MAKE_KC(VK_UP),
        MAKE_KC(VK_RIGHT),
        MAKE_KC(VK_DOWN),
        MAKE_KC(VK_SELECT),
        MAKE_KC(VK_PRINT),
        MAKE_KC(VK_EXECUTE),
        MAKE_KC(VK_SNAPSHOT),
        MAKE_KC(VK_INSERT),
        MAKE_KC(VK_DELETE),
        MAKE_KC(VK_HELP),
        MAKE_CUSTOM_KC("0", '0'),
        MAKE_CUSTOM_KC("1", '1'),
        MAKE_CUSTOM_KC("2", '2'),
        MAKE_CUSTOM_KC("3", '3'),
        MAKE_CUSTOM_KC("4", '4'),
        MAKE_CUSTOM_KC("5", '5'),
        MAKE_CUSTOM_KC("6", '6'),
        MAKE_CUSTOM_KC("7", '7'),
        MAKE_CUSTOM_KC("8", '8'),
        MAKE_CUSTOM_KC("9", '9'),
        MAKE_CUSTOM_KC("A", 'A'),
        MAKE_CUSTOM_KC("B", 'B'),
        MAKE_CUSTOM_KC("C", 'C'),
        MAKE_CUSTOM_KC("D", 'D'),
        MAKE_CUSTOM_KC("E", 'E'),
        MAKE_CUSTOM_KC("F", 'F'),
        MAKE_CUSTOM_KC("G", 'G'),
        MAKE_CUSTOM_KC("H", 'H'),
        MAKE_CUSTOM_KC("I", 'I'),
        MAKE_CUSTOM_KC("J", 'J'),
        MAKE_CUSTOM_KC("K", 'K'),
        MAKE_CUSTOM_KC("L", 'L'),
        MAKE_CUSTOM_KC("M", 'M'),
        MAKE_CUSTOM_KC("N", 'N'),
        MAKE_CUSTOM_KC("O", 'O'),
        MAKE_CUSTOM_KC("P", 'P'),
        MAKE_CUSTOM_KC("Q", 'Q'),
        MAKE_CUSTOM_KC("R", 'R'),
        MAKE_CUSTOM_KC("S", 'S'),
        MAKE_CUSTOM_KC("T", 'T'),
        MAKE_CUSTOM_KC("U", 'U'),
        MAKE_CUSTOM_KC("V", 'V'),
        MAKE_CUSTOM_KC("W", 'W'),
        MAKE_CUSTOM_KC("X", 'X'),
        MAKE_CUSTOM_KC("Y", 'Y'),
        MAKE_CUSTOM_KC("Z", 'Z'),
        MAKE_KC(VK_LWIN),
        MAKE_KC(VK_RWIN),
        MAKE_KC(VK_APPS),
        MAKE_KC(VK_SLEEP),
        MAKE_KC(VK_NUMPAD0),
        MAKE_KC(VK_NUMPAD1),
        MAKE_KC(VK_NUMPAD2),
        MAKE_KC(VK_NUMPAD3),
        MAKE_KC(VK_NUMPAD4),
        MAKE_KC(VK_NUMPAD5),
        MAKE_KC(VK_NUMPAD6),
        MAKE_KC(VK_NUMPAD7),
        MAKE_KC(VK_NUMPAD8),
        MAKE_KC(VK_NUMPAD9),
        MAKE_KC(VK_MULTIPLY),
        MAKE_KC(VK_ADD),
        MAKE_KC(VK_SEPARATOR),
        MAKE_KC(VK_SUBTRACT),
        MAKE_KC(VK_DECIMAL),
        MAKE_KC(VK_DIVIDE),
        MAKE_KC(VK_F1),
        MAKE_KC(VK_F2),
        MAKE_KC(VK_F3),
        MAKE_KC(VK_F4),
        MAKE_KC(VK_F5),
        MAKE_KC(VK_F6),
        MAKE_KC(VK_F7),
        MAKE_KC(VK_F8),
        MAKE_KC(VK_F9),
        MAKE_KC(VK_F10),
        MAKE_KC(VK_F11),
        MAKE_KC(VK_F12),
        MAKE_KC(VK_F13),
        MAKE_KC(VK_F14),
        MAKE_KC(VK_F15),
        MAKE_KC(VK_F16),
        MAKE_KC(VK_F17),
        MAKE_KC(VK_F18),
        MAKE_KC(VK_F19),
        MAKE_KC(VK_F20),
        MAKE_KC(VK_F21),
        MAKE_KC(VK_F22),
        MAKE_KC(VK_F23),
        MAKE_KC(VK_F24),
        MAKE_KC(VK_NUMLOCK),
        MAKE_KC(VK_SCROLL),
        MAKE_KC(VK_LSHIFT),
        MAKE_KC(VK_RSHIFT),
        MAKE_KC(VK_LCONTROL),
        MAKE_KC(VK_RCONTROL),
        MAKE_KC(VK_LMENU),
        MAKE_KC(VK_RMENU),
        MAKE_KC(VK_BROWSER_BACK),
        MAKE_KC(VK_BROWSER_FORWARD),
        MAKE_KC(VK_BROWSER_REFRESH),
        MAKE_KC(VK_BROWSER_STOP),
        MAKE_KC(VK_BROWSER_SEARCH),
        MAKE_KC(VK_BROWSER_FAVORITES),
        MAKE_KC(VK_BROWSER_HOME),
        MAKE_KC(VK_VOLUME_MUTE),
        MAKE_KC(VK_VOLUME_DOWN),
        MAKE_KC(VK_VOLUME_UP),
        MAKE_KC(VK_MEDIA_NEXT_TRACK),
        MAKE_KC(VK_MEDIA_PREV_TRACK),
        MAKE_KC(VK_MEDIA_STOP),
        MAKE_KC(VK_MEDIA_PLAY_PAUSE),
        MAKE_KC(VK_LAUNCH_MAIL),
        MAKE_KC(VK_LAUNCH_MEDIA_SELECT),
        MAKE_KC(VK_LAUNCH_APP1),
        MAKE_KC(VK_LAUNCH_APP2),
        MAKE_KC(VK_OEM_1),
        MAKE_KC(VK_OEM_PLUS),
        MAKE_KC(VK_OEM_COMMA),
        MAKE_KC(VK_OEM_MINUS),
        MAKE_KC(VK_OEM_PERIOD),
        MAKE_KC(VK_OEM_2),
        MAKE_KC(VK_OEM_3),
        MAKE_KC(VK_OEM_4),
        MAKE_KC(VK_OEM_5),
        MAKE_KC(VK_OEM_6),
        MAKE_KC(VK_OEM_7),
        MAKE_KC(VK_OEM_8),
        MAKE_KC(VK_OEM_102),
        MAKE_KC(VK_PROCESSKEY),
        MAKE_KC(VK_PACKET),
        MAKE_KC(VK_ATTN),
        MAKE_KC(VK_CRSEL),
        MAKE_KC(VK_EXSEL),
        MAKE_KC(VK_EREOF),
        MAKE_KC(VK_PLAY),
        MAKE_KC(VK_ZOOM),
        MAKE_KC(VK_NONAME),
        MAKE_KC(VK_PA1),
        MAKE_KC(VK_OEM_CLEAR)
    };

    const auto result = std::find_if(KEYCODES.cbegin(), KEYCODES.cend(), [&](const Keycode& kc) {
        return key_name == kc.name;
    });
    return result == KEYCODES.cend() ? -1 : result->key;
}

static constexpr std::string_view trim_str(std::string_view str)
{
    if (str.empty())
        return str;

    const auto begin = str.find_first_not_of(' ');
    const auto end = str.find_last_not_of(' ') + 1;

    return str.substr(begin, end == std::string_view::npos ? end : end - begin);
}

static_assert(trim_str("") == "");
static_assert(trim_str("hello") == "hello");
static_assert(trim_str("  hello  ") == "hello");
static_assert(trim_str("  hello") == "hello");
static_assert(trim_str("hello  ") == "hello");

int utils::get_keybinding()
{
    std::ifstream f("Y0LSF_keybind.txt");
    if (!f)
        return VK_TAB;

    std::string line;
    if (!std::getline(f, line))
        return VK_TAB;

    const auto key = get_keycode(trim_str(line));
    if (key == -1)
        return VK_TAB;

    return key;
}