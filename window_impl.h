#ifndef INCLUDE_GUARD_WINDOW_IMPL_H
#define INCLUDE_GUARD_WINDOW_IMPL_H

#include "window.h"

#include <string>
#include <unordered_map>
#include <functional>

#define WIN32_LEAN_AND_MEAN
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
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	impl_t(std::function<HWND()> init);
	virtual ~impl_t() = 0;

	HWND handle();
};

#endif
