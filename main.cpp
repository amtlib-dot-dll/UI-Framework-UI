#include <string>
#include <cassert>
#include <system_error>
#include <memory>

#include "main_window.h"
#include "message_queue.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int main() {
	using namespace std::string_literals;

	constexpr auto CLASS_NAME = L"main";

	auto window = std::make_unique<main_window_t>();

	return message_queue();
}
