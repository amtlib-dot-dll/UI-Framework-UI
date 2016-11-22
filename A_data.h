#ifndef INCLUDE_GUARD_A_DATA_H
#define INCLUDE_GUARD_A_DATA_H

#include <type_traits>

#include <Windows.h>

struct A_data_t {
    HWND hWnd;
};

static_assert(std::is_standard_layout<A_data_t>::value, "A_data_t");

#endif