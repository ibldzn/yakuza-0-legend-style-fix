#pragma once
#include <iostream>
#include <intrin.h>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#  include <Windows.h>
#  include <Xinput.h>
#undef WIN32_LEAN_AND_MEAN

#include "../mem/mem.h"

namespace hooks
{
	void init();

	namespace change_style
	{
		using fn = __int64(__fastcall*)(unsigned __int64 is_majima, int style);
		__int64 __fastcall hook_func(unsigned __int64 is_majima, int style);
	}

	namespace get_key_press
	{
		using fn = signed __int64(__fastcall*)(__int64 a1);
		signed __int64 __fastcall hook_func(__int64 a1);
	}

	namespace get_current_style
	{
		using fn = signed __int64(__fastcall*)();
		signed __int64 __fastcall hook_func();
	}
}