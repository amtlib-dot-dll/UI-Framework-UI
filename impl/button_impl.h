#ifndef INCLUDE_GUARD_BUTTON_IMPL_H
#define INCLUDE_GUARD_BUTTON_IMPL_H

#include "button.h"

#include "main_window.h"

#include <string>

#define NOMINMAX
#include <Windows.h>

class button_t::impl_t {
	HWND hButton;
	int x;
	int y;
	int width;
	int height;
	std::string text;
	uintptr_t id;

public:
	impl_t(uintptr_t id, std::string text, int x, int y, int width, int height, HWND hWnd);
};

#endif