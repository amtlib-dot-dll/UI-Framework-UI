#ifndef INCLUDE_GUARD_BUTTON_H
#define INCLUDE_GUARD_BUTTON_H

#include "window.h"

#include <memory>
#include <string>

class button_t {
	class impl_t;
	std::unique_ptr<impl_t> impl_;

public:
	button_t(uintptr_t id, std::string text, int x, int y, int width, int height, window_t& window);
	~button_t();
};

#endif