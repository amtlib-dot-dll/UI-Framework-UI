#include "button.h"

#include "window.h"

#include <cassert>
#include <thread>
#include <locale>
#include <string>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <CommCtrl.h>

button_t::button_t(uintptr_t id, std::string text, int x, int y, int width, int height, window_t& window) :id_(id), text_(text), x_(x), y_(y), width_(width), height_(height) {
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t> converter;

	hButton_ = CreateWindowExW(0, L"BUTTON", converter.from_bytes(text).c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_COMMANDLINK, x, y, width, height, window.handle(), reinterpret_cast<HMENU>(id), reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(window.handle(), GWLP_HINSTANCE)), nullptr);
	assert(hButton_ != nullptr);
}
