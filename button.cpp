#include "button.h"

#include <cassert>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <CommCtrl.h>

struct button_t::impl_t {
	impl_t() {
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
	HWND hButton;
};

button_t::button_t():impl(new impl_t) {}

button_t::~button_t() = default;