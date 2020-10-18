#ifndef ASSIGNMENT_3__BUFFER_H_
#define ASSIGNMENT_3__BUFFER_H_

#include <memory>

class Buffer {
public:
	explicit Buffer(int size)
		: _size(size) {}

private:
	const size_t _size;
};

#endif //ASSIGNMENT_3__BUFFER_H_
