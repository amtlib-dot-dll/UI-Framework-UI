#ifndef INCLUDE_GUARD_WINDOW_IMPL_H
#define INCLUDE_GUARD_WINDOW_IMPL_H

#include "window.h"

#include <string>
#include <unordered_map>
#include <functional>
#include <thread>

#define NOMINMAX
#include <Windows.h>

class window_t::impl_t {
protected:
	HWND hWnd_;
	std::unordered_map<UINT, std::function<LRESULT(WPARAM wParam, LPARAM lParam)>> handlers_;
	std::string title_;
	int x_;
	int y_;
	int width_;
	int height_;

	std::thread thread_;

public:
	impl_t(std::string title, int width, int height);
	impl_t(std::string title, int x, int y, int width, int height);
	~impl_t();

	HWND handle();
	std::thread& thread();
};

#endif
