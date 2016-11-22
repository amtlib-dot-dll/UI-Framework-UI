#pragma once
#include <memory>
#include <functional>
#include <type_traits>

class A {
    struct impl_t;
    std::unique_ptr<impl_t> impl;

public:
    A();
    ~A();
};

static_assert(std::is_standard_layout<A>::value, "A");
