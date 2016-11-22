#pragma once

#include "A.h"

#include <memory>
#include <functional>

class B {
    struct impl_t;
    std::unique_ptr<impl_t> impl;
public:
    B();
    ~B();

    void call(A& a);
};

static_assert(std::is_standard_layout<B>::value, "B");