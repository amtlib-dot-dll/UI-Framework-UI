#ifndef INCLUDE_GUARD_WINDOW_H
#define INCLUDE_GUARD_WINDOW_H

#include <string>
#include <memory>
#include <thread>

class window_t {
protected:
	class impl_t;
	std::unique_ptr<impl_t> impl_;

public:
	window_t(std::string title, int width, int height);
	window_t(std::string title, int x, int y, int width, int height);
	~window_t();

	std::thread& thread();
	impl_t& get_impl();
};

#endif
