#ifndef INCLUDE_GUARD_BUTTON_H
#define INCLUDE_GUARD_BUTTON_H

#include "main_window.h"

#include <memory>
#include <string>

class button_t {
	class impl_t;
	std::unique_ptr<impl_t> impl;

public:
	button_t(uintptr_t id, std::string text, int x, int y, int width, int height, main_window_t& window);
	~button_t();
};

#endif