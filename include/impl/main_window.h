#ifndef INCLUDE_GUARD_IMPL_MAIN_WINDOW_H
#define INCLUDE_GUARD_IMPL_MAIN_WINDOW_H

#include <memory>

class main_window_t::impl_t {
public:
 	impl_t();

	LRESULT handle_message(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static ATOM get_window_class();
private:
	HWND hWnd;
};

#endif
