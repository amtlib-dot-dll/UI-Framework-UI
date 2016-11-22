#include "A.h"
#include "A_data.h"

#include <type_traits>

#include <Windows.h>

struct A::impl_t : A_data_t {};

A::A() :impl(new impl_t) {
    static_assert(std::is_standard_layout<A::impl_t>::value, "A::impl_t");
}

A::~A() = default;
