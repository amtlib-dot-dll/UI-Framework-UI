#include "main_window.h"
#include "impl/main_window_impl.h"

#include <vector>
#include <memory>
#include <string>
#include <locale>
#include <cassert>
#include <mutex>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <CommCtrl.h>

main_window_t::impl_t::impl_t(std::string title, int width, int height) :impl_t(title, CW_USEDEFAULT, CW_USEDEFAULT, width, height) {}

main_window_t::impl_t::impl_t(std::string title, int x, int y, int width, int height) : window_t::impl_t([&]()->HWND {
	static std::once_flag flag;
	static ATOM atom;
	if (atom == 0) {
		std::call_once(flag, []() {
			auto wcx = WNDCLASSEXW{};
			wcx.cbSize = sizeof(wcx);
			wcx.lpszClassName = L"main";
			wcx.lpfnWndProc = window_t::impl_t::WndProc;
			wcx.hCursor = LoadCursorW(nullptr, IDC_ARROW);
			assert(wcx.hCursor != nullptr);

			wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);

			atom = RegisterClassExW(&wcx);
			assert(atom != 0);
		});
	}

	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t> converter;

	auto hWnd = CreateWindowExW(0, reinterpret_cast<LPCWSTR>(atom), converter.from_bytes(title).c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, nullptr, nullptr);
	assert(hWnd != nullptr);
	return hWnd;
}) {
	handlers.insert({ WM_DESTROY, [](WPARAM wParam, LPARAM lParam)->LRESULT {
		PostQuitMessage(0);
		return 0;
	} });
}

main_window_t::main_window_t(std::string title, int x, int y, int width, int height) :impl(new impl_t{ title, x, y, width, height }) {}

main_window_t::main_window_t(std::string title, int width, int height) : impl(new impl_t{ title, width, height }) {}

main_window_t::~main_window_t() = default;

main_window_t::impl_t& main_window_t::get_impl() {
	return *impl;
}
