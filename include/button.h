#ifndef INCLUDE_GUARD_BUTTON_H
#define INCLUDE_GUARD_BUTTON_H

#include "main_window.h"

#include <memory>

class button_t {
	class impl_t;
	std::unique_ptr<impl_t> impl;

public:
	button_t(main_window_t& window);
	~button_t();
 };

#endif