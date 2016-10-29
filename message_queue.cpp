#include "message_queue.h"

#include <cassert>

#include <Windows.h>

int message_queue() {
	MSG msg;
	for (;;) {
		switch (GetMessageW(&msg, nullptr, 0, 0)) {
			case -1:
				assert(false);
			case 0:
				return static_cast<int>(msg.wParam);
			default:
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
		}
	}
}
