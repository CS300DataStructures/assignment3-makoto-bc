#ifndef ASSIGNMENT_3__BUFFER_H_
#define ASSIGNMENT_3__BUFFER_H_

#include <memory>
#include <ostream>
#include <vector>
#include "Packet.h"

namespace network {

/**
 * FIFO container based on a fixed stack.
 * @tparam T Item type
 */
template<class T>
class Queue {
public:
	/**
	 * Used for pushBack().
	 */
	enum class PushBackResult {
		Added,
		Dropped,
	};

	/**
	 * Initializes queue with given capacity.
	 */
	explicit Queue(int capacity)
		: _array(std::make_unique<T[]>(static_cast<size_t>(capacity)))
		  , _capacity(static_cast<size_t>(capacity))
		  , _front(0)
		  , _size(0) {}

	/**
	 * Initializes queue with given capacity.
	 */
	explicit Queue(size_t capacity)
		: _array(std::make_unique<T[]>(capacity))
		  , _capacity(capacity)
		  , _front(0)
		  , _size(0) {}

	/**
	 * Sets capacity to list size and copies items in list to queue.
	 */
	Queue(const std::initializer_list<T>& list) // NOLINT(cppcoreguidelines-pro-type-member-init)
		: Queue(list.size()) {
		for (T item : list) {
			pushBack(item);
		}
	}

	Queue(const Queue<T>& queue) // NOLINT(cppcoreguidelines-pro-type-member-init)
		: Queue(queue._capacity) {
		for (size_t i = 0; i < queue._size; ++i) {
			pushBack(queue[i]);
		}
	}

	Queue(Queue&& queue) noexcept {
		_array = std::move(queue._array);
		_capacity = queue._capacity;
		_front = queue._front;
		_size = queue._size;
	}

	/**
	 * Pushes item to back of queue if there is space.
	 * @return PushBackResult::Added if item was added to queue. PushBackResult::Dropped if item
	 * was not added to queue.
	 */
	PushBackResult pushBack(T item) {
		if (_size == _capacity) {
			return PushBackResult::Dropped;
		}
		_array[(_front + _size) % _capacity] = std::move(item);
		++_size;
		return PushBackResult::Added;
	}

	/**
	 * Removes first item in queue if queue is not empty.
	 */
	void popFront() {
		if (_size > 0) {
			_front = (_front + 1) % _capacity;
			--_size;
		}
	}

	/**
	 * Removes item at index if it exists.
	 * @throws std::out_of_range index is out of range
	 */
	void remove(size_t index) {
		if (index >= _size) {
			throw std::out_of_range("index is out of range");
		}

		if (index == 0) {
			popFront();
			return;
		}

		for (size_t i = 0; i < _size - index; ++i) {
			_array[(_front + i + index) % _capacity]
				= std::move(_array[(_front + i + index + 1) % _capacity]);
		}
		--_size;
	}

	size_t size() const {
		return _size;
	}

	T& operator[](size_t index) {
		return const_cast<T&>(const_cast<const Queue&>(*this).operator[](index));
	}

	const T& operator[](size_t index) const {
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
			if (i < queue._size - 1) {
				os << ", ";
			}
		}
		os << '}';
		return os;
	}

private:
	std::unique_ptr<T[]> _array;
	size_t _capacity;
	size_t _front;
	size_t _size;
};

/**
 * Stores Packets in a Queue with a fixed capacity.
 */
using Buffer = Queue<Packet>;

/**
 * Determines response times of packets. Each packet is processed sequentially, as if we are using
 * a horribly designed server.
 * @param packets Input packets
 * @param pBuffer Buffer for packets
 * @return Response times
 */
std::vector<Response> processPackets(const std::vector<Packet>& packets, Buffer* pBuffer);

}

#endif //ASSIGNMENT_3__BUFFER_H_
