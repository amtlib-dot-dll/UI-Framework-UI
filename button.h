#ifndef INCLUDE_GUARD_BUTTON_H
#define INCLUDE_GUARD_BUTTON_H

#include "window.h"

#include <memory>
#include <string>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

class button_t {
	HWND hButton_;
	int x_;
	int y_;
	int width_;
	int height_;
	std::string text_;
	uintptr_t id_;

public:
	button_t(uintptr_t id, std::string text, int x, int y, int width, int height, window_t& window);
};

#endif