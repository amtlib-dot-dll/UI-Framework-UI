#include "main_window.h"
#include "impl/main_window_impl.h"

#include <vector>
#include <memory>
#include <cassert>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <CommCtrl.h>

main_window_t::impl_t::impl_t() {
	hWnd = CreateWindowExW(0, reinterpret_cast<LPCWSTR>(get_window_class()), L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, nullptr, nullptr);
	assert(hWnd != nullptr);

	SetLastError(ERROR_SUCCESS);
	assert(!(SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) == 0 && GetLastError() != ERROR_SUCCESS));

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

HWND main_window_t::impl_t::handle() {
	return hWnd;
}

LRESULT main_window_t::impl_t::handle_message(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_COMMAND:
			if (LOWORD(wParam) == 123) {
				MessageBoxA(hWnd, "Message", "Caption", MB_ABORTRETRYIGNORE);
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
}

ATOM main_window_t::impl_t::get_window_class() {
	struct window_class_t {
		ATOM atom;
		window_class_t() {
			auto wcx = WNDCLASSEXW{};
			wcx.cbSize = sizeof(wcx);
			wcx.lpszClassName = L"main";
			wcx.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ->LRESULT {
				main_window_t::impl_t* impl = reinterpret_cast<main_window_t::impl_t*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

				if (impl == nullptr) {
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
				}

				return impl->handle_message(uMsg, wParam, lParam);
			};
			wcx.hCursor = LoadCursorW(nullptr, IDC_ARROW);
			assert(wcx.hCursor != nullptr);

			wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);

			atom = RegisterClassExW(&wcx);
			assert(atom != 0);
		}
	};

	static window_class_t window_class;
	return window_class.atom;
}

main_window_t::main_window_t() :impl(new impl_t) {}

main_window_t::~main_window_t() = default;

main_window_t::impl_t& main_window_t::get_impl() {
	return *impl;
}
