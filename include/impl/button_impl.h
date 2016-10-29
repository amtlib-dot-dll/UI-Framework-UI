#ifndef INCLUDE_GUARD_BUTTON_IMPL_H
#define INCLUDE_GUARD_BUTTON_IMPL_H

#include "button.h"

#include "main_window.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

class button_t::impl_t {
	HWND hButton;

public:
	impl_t(HWND hWnd);
};

#endif