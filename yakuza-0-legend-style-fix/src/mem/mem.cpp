#include "mem.h"

static bool initialized = false;

void mem::init()
{
    if (!initialized)
        if (MH_Initialize() != MH_OK)
            throw std::runtime_error("mem::init - Failed to initialize minhook!");

    initialized = true;
}

bool mem::destroy()
{
    if (!initialized)
        return true;

    if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
        return false;

    if (MH_Uninitialize() != MH_OK)
        return false;

    return true;
}

uintptr_t mem::ida_pattern_scan(const char* pattern)
{
    static auto pattern_to_bytes = [](const char* _pattern)
    {
        char* start = const_cast<char*>(_pattern);
        char* end = start + strlen(_pattern);
        std::vector<int> ret = {};

        for (char* current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ret.push_back(-1);
                current++;
            }
            else
            {
                ret.push_back(std::strtoul(current, &current, 16));
            }
        }

        return ret;
    };

    const auto pattern_bytes = pattern_to_bytes(pattern);
    const auto pattern_data = pattern_bytes.data();
    const auto pattern_size = pattern_bytes.size();

    static const HMODULE mod_handle = GetModuleHandleA(NULL);
    if (!mod_handle)
        return uintptr_t();

    const BYTE* image_bytes = reinterpret_cast<BYTE*>(mod_handle);

    MODULEINFO mod_info;
    GetModuleInformation(GetCurrentProcess(), mod_handle, &mod_info, sizeof(MODULEINFO));

    const DWORD image_size = mod_info.SizeOfImage;

    for (size_t i = 0; i < image_size - pattern_size; ++i)
    {
        bool found = true;

        for (int j = 0; j < pattern_size; ++j)
        {
            if (image_bytes[i + j] != pattern_data[j] && pattern_data[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
            return reinterpret_cast<uintptr_t>(&image_bytes[i]);
    }

    return uintptr_t();
}

uintptr_t mem::follow(uintptr_t base, uintptr_t offset)
{
    return base + *reinterpret_cast<int32_t*>(base + offset) + 5;
}
