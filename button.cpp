#include "button.h"
#include "impl/button_impl.h"

#include "main_window.h"
#include "impl/main_window_impl.h"

#include <cassert>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <CommCtrl.h>

button_t::impl_t::impl_t(HWND hWnd) {
	HWND hwndCommandLink = CreateWindowExW(0,
		L"BUTTON",
		L"OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_COMMANDLINK,
		10,
		10,
		100,
		100,
		nullptr,
		nullptr,
		nullptr,
		nullptr);
	assert(hwndCommandLink != nullptr);
	SendMessageW(hwndCommandLink, WM_SETTEXT, 0, (LPARAM)L"Command link");
	SendMessageW(hwndCommandLink, BCM_SETNOTE, 0, (LPARAM)L"with note");
}


button_t::button_t(main_window_t& window) :impl(new impl_t{ window.get_impl().handle() }) {}

button_t::~button_t() = default;
