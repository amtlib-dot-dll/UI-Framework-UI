#include "main_window.h"
#include "impl/main_window_impl.h"

#include <vector>
#include <memory>
#include <string>
#include <locale>
#include <cassert>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <CommCtrl.h>

main_window_t::impl_t::impl_t(std::string title, int width, int height) :impl_t(title, CW_USEDEFAULT, CW_USEDEFAULT, width, height) {}

main_window_t::impl_t::impl_t(std::string title, int x, int y, int width, int height) : title(title), width(width), height(height) {
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t> converter;

	hWnd = CreateWindowExW(0, reinterpret_cast<LPCWSTR>(get_window_class_atom()), converter.from_bytes(title).c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, nullptr, nullptr);
	assert(hWnd != nullptr);

	SetLastError(ERROR_SUCCESS);
	assert(!(SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) == 0 && GetLastError() != ERROR_SUCCESS));

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	auto rect = RECT{};
	assert(GetWindowRect(hWnd, &rect) != 0);
	this->x = rect.left;
	this->y = rect.top;

	handlers.insert({ WM_DESTROY, [&](WPARAM wParam, LPARAM lParam)->LRESULT {
		PostQuitMessage(0);
		return 0;
	} });
}

HWND main_window_t::impl_t::handle() {
	return hWnd;
}

ATOM main_window_t::impl_t::get_window_class_atom() {
	struct window_class_t {
		ATOM atom;
		window_class_t() {
			auto wcx = WNDCLASSEXW{};
			wcx.cbSize = sizeof(wcx);
			wcx.lpszClassName = L"main";
			wcx.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ->LRESULT {
				main_window_t::impl_t* impl = reinterpret_cast<main_window_t::impl_t*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

				if (impl == nullptr || impl->handlers.count(uMsg) == 0) {
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
				}

				return impl->handlers.at(uMsg)(wParam, lParam);
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

main_window_t::main_window_t(std::string title, int x, int y, int width, int height) :impl(new impl_t{ title, x, y, width, height }) {}

main_window_t::main_window_t(std::string title, int width, int height) : impl(new impl_t{ title, width, height }) {}

main_window_t::~main_window_t() = default;

main_window_t::impl_t& main_window_t::get_impl() {
	return *impl;
}
