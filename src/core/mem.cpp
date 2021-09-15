#include "mem.hpp"

#include <Windows.h>
#include <vector>

uintptr_t mem::pattern_scan(std::string_view module_name, std::string_view pattern)
{
    const auto bytes = [](std::string_view str) -> std::vector<int>
    {
        std::vector<int> ret = {};

        for (size_t i = 0, length = str.length(); i < length; ++i)
        {
            if (str[i] == '?')
            {
                ++i;

                if (i < length && str[i] == '?')
                    ++i;

                ret.emplace_back(-1);
            }
            else
            {
                ret.emplace_back(std::strtoul(&str[i], nullptr, 16));
                i += 2;
            }
        }

        return ret;
    }(pattern);

    uint8_t* mod = reinterpret_cast<uint8_t*>(GetModuleHandleA(module_name.data()));
    if (!mod)
        return {};

    IMAGE_DOS_HEADER* dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(mod);
    IMAGE_NT_HEADERS* nt_headers = reinterpret_cast<IMAGE_NT_HEADERS*>(mod + dos_header->e_lfanew);
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE || nt_headers->Signature != IMAGE_NT_SIGNATURE)
        return {};

    size_t mod_size = nt_headers->OptionalHeader.SizeOfImage;

    for (size_t i = 0; i < mod_size - bytes.size(); ++i)
    {
        bool found = true;

        for (size_t j = 0; j < bytes.size(); ++j)
        {
            if (mod[i + j] != bytes[j] && bytes[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
            return reinterpret_cast<uintptr_t>(&mod[i]);
    }

    return {};
}

uintptr_t mem::follow_rel32(uintptr_t address, ptrdiff_t offset)
{
    return address + *reinterpret_cast<int*>(address + offset) + 5;
}
