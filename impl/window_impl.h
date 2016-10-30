#ifndef INCLUDE_GUARD_WINDOW_IMPL_H
#define INCLUDE_GUARD_WINDOW_IMPL_H

#include "window.h"

#include <string>
#include <unordered_map>
#include <functional>

#define NOMINMAX
#include <Windows.h>

class window_t::impl_t {
protected:
	HWND hWnd;
	std::unordered_map<UINT, std::function<LRESULT(WPARAM wParam, LPARAM lParam)>> handlers;
	std::string title;
	int x;
	int y;
	int width;
	int height;

public:
	impl_t(std::string title, int width, int height);
	impl_t(std::string title, int x, int y, int width, int height);
	~impl_t();

	HWND handle();
};

#endif
