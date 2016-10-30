#include "window.h"
#include "impl/window_impl.h"

#include <string>
#include <locale>
#include <cassert>
#include <functional>
#include <mutex>

#define NOMINMAX
#include <Windows.h>

window_t::impl_t::impl_t(std::string title, int width, int height) :impl_t(title, CW_USEDEFAULT, CW_USEDEFAULT, width, height) {}

window_t::impl_t::impl_t(std::string title, int x, int y, int width, int height) : title_(title), width_(width), height_(height) {
	static std::once_flag flag;
	static ATOM atom;
	if (atom == 0) {
		std::call_once(flag, [] {
			auto wcx = WNDCLASSEXW{};
			wcx.cbSize = sizeof(wcx);
			wcx.lpszClassName = L"window";
			wcx.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {
				window_t::impl_t* impl = reinterpret_cast<window_t::impl_t*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

				if (impl == nullptr || impl->handlers_.count(uMsg) == 0) {
					return DefWindowProcW(hWnd, uMsg, wParam, lParam);
				}

				return impl->handlers_.at(uMsg)(wParam, lParam);
			};
			wcx.hCursor = LoadCursorW(nullptr, IDC_ARROW);
			assert(wcx.hCursor != nullptr);

			wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);

			atom = RegisterClassExW(&wcx);
			assert(atom != 0);
		});
	}

	handlers_.insert({ WM_DESTROY, [](WPARAM wParam, LPARAM lParam)->LRESULT {
		PostQuitMessage(0);
		return 0;
	} });

	thread_ = std::thread{ [&] {
		std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t> converter;

		hWnd_ = CreateWindowExW(0, reinterpret_cast<LPCWSTR>(atom), converter.from_bytes(title_).c_str(), WS_OVERLAPPEDWINDOW, x_, y_, width_, height_, nullptr, nullptr, nullptr, nullptr);
		assert(hWnd_ != nullptr);

		SetLastError(ERROR_SUCCESS);
		assert(!(SetWindowLongPtrW(hWnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) == 0 && GetLastError() != ERROR_SUCCESS));

		ShowWindow(hWnd_, SW_SHOWDEFAULT);

		auto rect = RECT{};
		assert(GetWindowRect(hWnd_, &rect) != 0);
		x_ = rect.left;
		y_ = rect.top;

		MSG msg;
		for (;;) {
			switch (GetMessageW(&msg, nullptr, 0, 0)) {
				case -1:
					assert(false);
				case 0:
					return;
				default:
					TranslateMessage(&msg);
					DispatchMessageW(&msg);
			}
		}
	} };
}

window_t::impl_t::~impl_t() = default;

HWND window_t::impl_t::handle() {
	return hWnd_;
}

std::thread& window_t::impl_t::thread() {
	return thread_;
}

window_t::window_t(std::string title, int width, int height) :impl_(new impl_t{ title, width, height }) {}

window_t::window_t(std::string title, int x, int y, int width, int height) : impl_(new impl_t{ title, x, y, width, height }) {}

window_t::~window_t() = default;

std::thread& window_t::thread() {
	return impl_->thread();
}

window_t::impl_t& window_t::get_impl() {
	return *impl_;
}
