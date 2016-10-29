#ifndef INCLUDE_GUARD_MAIN_WINDOW_H
#define INCLUDE_GUARD_MAIN_WINDOW_H

#include <memory>
#include <string>

class main_window_t {
	class impl_t;
	std::unique_ptr<impl_t> impl;

public:
	main_window_t(std::string title, int width, int height);
	main_window_t(std::string title, int x, int y, int width, int height);
	~main_window_t();

	impl_t& get_impl();
};

#endif
