#include <string>
#include <cassert>
#include <system_error>
#include <memory>

#include "window.h"
#include "button.h"
#include "message_queue.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int main() {
	using namespace std::string_literals;

	constexpr auto CLASS_NAME = L"main";

	auto window = std::make_unique<window_t>(u8"Window"s, 500, 200);
	auto window2 = std::make_unique<window_t>(u8"Window2"s, 500, 200);
	//auto button = std::make_unique<button_t>(1, u8"Text"s, 3, 3, 280, 100, *window);
	//auto button2 = std::make_unique<button_t>(1, u8"Text2"s, 10, 3, 280, 100, *window2);

	window->thread().join();
	window2->thread().join();

	return 0;
}
