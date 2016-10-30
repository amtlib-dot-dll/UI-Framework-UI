#ifndef INCLUDE_GUARD_BUTTON_IMPL_H
#define INCLUDE_GUARD_BUTTON_IMPL_H

#include "button.h"

#include "window.h"

#include <string>

#define NOMINMAX
#include <Windows.h>

class button_t::impl_t {
	HWND hButton_;
	int x_;
	int y_;
	int width_;
	int height_;
	std::string text_;
	uintptr_t id_;

public:
	impl_t(uintptr_t id, std::string text, int x, int y, int width, int height, HWND hWnd);
};

#endif