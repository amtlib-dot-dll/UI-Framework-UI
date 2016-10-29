#include <string>
#include <cassert>
#include <system_error>
#include <memory>

#include "main_window.h"
#include "button.h"
#include "message_queue.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int main() {
	using namespace std::string_literals;

	constexpr auto CLASS_NAME = L"main";

	auto window = std::make_unique<main_window_t>();
	auto button = std::make_unique<button_t>(1, u8"Text"s, 3, 3, 280, 100, *window);

	return message_queue();
}
