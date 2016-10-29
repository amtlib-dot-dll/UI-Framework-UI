#ifndef INCLUDE_GUARD_BUTTON_H
#define INCLUDE_GUARD_BUTTON_H

#include <memory>

class button_t {
public:
	button_t();
	~button_t();
private:
	struct impl_t;
	std::unique_ptr<impl_t> impl;
};

#endif