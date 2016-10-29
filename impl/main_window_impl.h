#ifndef INCLUDE_GUARD_MAIN_WINDOW_IMPL_H
#define INCLUDE_GUARD_MAIN_WINDOW_IMPL_H

#include "main_window.h"

#include <string>
#include <unordered_map>
#include <functional>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

class main_window_t::impl_t {
	HWND hWnd;
	std::unordered_map<UINT, std::function<LRESULT(WPARAM wParam, LPARAM lParam)>> handlers;
	std::string title;
	int x;
	int y;
	int width;
	int height;

	static ATOM get_window_class_atom();
public:
	impl_t(std::string title, int width, int height);
	impl_t(std::string title, int x, int y, int width, int height);

	HWND handle();
};

#endif
