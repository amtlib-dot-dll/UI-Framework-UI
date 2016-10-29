#ifndef INCLUDE_GUARD_MAIN_WINDOW_IMPL_H
#define INCLUDE_GUARD_MAIN_WINDOW_IMPL_H

#include "main_window.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

class main_window_t::impl_t {
	HWND hWnd;

	LRESULT handle_message(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static ATOM get_window_class();
public:
 	impl_t();

	HWND handle();
};

#endif