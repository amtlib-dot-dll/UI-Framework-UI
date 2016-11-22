#ifndef INCLUDE_GUARD_WINDOW_H
#define INCLUDE_GUARD_WINDOW_H

#include <string>
#include <memory>
#include <thread>
#include <unordered_map>
#include <functional>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

class window_t {
protected:
	::HWND hWnd_;
	std::unordered_map<::UINT, std::function<::LRESULT(::WPARAM wParam, ::LPARAM lParam)>> handlers_;
	std::string title_;
	int x_;
	int y_;
	int width_;
	int height_;

	std::thread thread_;

public:
	window_t(std::string title, int width, int height);
	window_t(std::string title, int x, int y, int width, int height);

	::HWND handle();
	std::thread& thread();
};

#endif
