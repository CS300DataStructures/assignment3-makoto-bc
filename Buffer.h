#ifndef ASSIGNMENT_3__BUFFER_H_
#define ASSIGNMENT_3__BUFFER_H_

#include <memory>
#include <ostream>
#include "Packet.h"

template<class T>
class Queue {
public:
	explicit Queue(int capacity)
		: _array(std::make_unique<T[]>(0))
		, _capacity(capacity)
		, _front(0)
		, _size(0) {}

	Queue(const std::initializer_list<T>& list) : Queue(list.size()) {
		for (T item : list) {
			pushBack(item);
		}
	}

	Queue(const Queue<T>& queue) : Queue(queue.size()) {
		for (size_t i = 0; i < queue._size; ++i) {
			pushBack(queue[i]);
		}
	}

	void pushBack(T item) {
		if (_size == _capacity) {
			return;
		}
		_array[(_front + _size) % _capacity] = std::move(item);
		++_size;
	}

	void popFront() {
		if (_size == 0) {
			return;
		}
		_front = (_front + 1) % _capacity;
		--_size;
	}

	size_t size() const {
		return _size;
	}

	T& operator[](size_t index) const {
		if (index >= _size) {
			throw std::out_of_range("index is out of range");
		}

		return _array[(_front + index) % _capacity];
	}

	bool operator==(const Queue<T>& rhs) const {
		if (_size != rhs._size) {
			return false;
		}

		for (size_t i = 0; i < _size; ++i) {
			if (operator[](i) != rhs[i]) {
				return false;
			}
		}
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os, const Queue& queue) {
		os << '{';
		for (size_t i = 0; i < queue._size; ++i) {
			os << queue[i];
			if (i != queue._size - 1) {
				os << ", ";
			}
		}
		os << '}';
		return os;
	}

	Queue& operator=(Queue&& queue) noexcept {
		_array = std::move(queue._array);
		_capacity = queue._capacity;
		_front = queue._front;
		_size = queue._size;
		return *this;
	}

private:
	std::unique_ptr<T[]> _array;
	const size_t _capacity;
	size_t _front;
	size_t _size;
};

using Buffer = Queue<Packet>;

#endif //ASSIGNMENT_3__BUFFER_H_
