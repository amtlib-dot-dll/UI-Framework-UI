#include "window.h"
#include "window_impl.h"

#include <string>
#include <locale>
#include <cassert>
#include <functional>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

window_t::impl_t::impl_t(std::function<HWND()> init) :hWnd(init()) {
	SetLastError(ERROR_SUCCESS);
	assert(!(SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) == 0 && GetLastError() != ERROR_SUCCESS));

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	auto rect = RECT{};
	assert(GetWindowRect(hWnd, &rect) != 0);
	x = rect.left;
	y = rect.top;
}

window_t::impl_t::~impl_t() = default;

HWND window_t::impl_t::handle() {
	return hWnd;
}

LRESULT CALLBACK window_t::impl_t::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	window_t::impl_t* impl = reinterpret_cast<window_t::impl_t*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

	if (impl == nullptr || impl->handlers.count(uMsg) == 0) {
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	return impl->handlers.at(uMsg)(wParam, lParam);
}

window_t::~window_t() = default;
