#include "button.h"
#include "impl/button_impl.h"

#include "window.h"
#include "impl/window_impl.h"

#include <cassert>
#include <thread>
#include <locale>
#include <string>

#define NOMINMAX
#include <Windows.h>
#include <CommCtrl.h>

button_t::impl_t::impl_t(uintptr_t id, std::string text, int x, int y, int width, int height, HWND hWnd) :id_(id), text_(text), x_(x), y_(y), width_(width), height_(height) {
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t> converter;

	hButton_ = CreateWindowExW(0, L"BUTTON", converter.from_bytes(text).c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_COMMANDLINK, x, y, width, height, hWnd, reinterpret_cast<HMENU>(id), reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hWnd, GWLP_HINSTANCE)), nullptr);
	assert(hButton_ != nullptr);
}

button_t::button_t(uintptr_t id, std::string text, int x, int y, int width, int height, window_t& window) :impl_(new impl_t{ id, text, x, y, width, height, window.get_impl().handle() }) {}

button_t::~button_t() = default;
