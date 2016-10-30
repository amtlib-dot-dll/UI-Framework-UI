#ifndef INCLUDE_GUARD_WINDOW_H
#define INCLUDE_GUARD_WINDOW_H

#include <string>

class window_t {
protected:
	class impl_t;

public:
	virtual	~window_t() = 0;
};

#endif
