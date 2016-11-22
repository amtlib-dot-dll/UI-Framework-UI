#include "B.h"

#include "A_data.h"

#include <memory>

#include <Windows.h>

struct B::impl_t {
    void call(A& a);
};

B::B() :impl(new impl_t) {}

B::~B() = default;

void B::call(A& a) {
    impl->call(a);
}

void B::impl_t::call(A& a) {
    A_data_t &p = *reinterpret_cast<std::unique_ptr<A_data_t>*>(&a)->get();
    GetWindowTextLengthW(p.hWnd);
}
