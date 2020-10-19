#ifndef ASSIGNMENT_3__PACKET_H_
#define ASSIGNMENT_3__PACKET_H_

#include "time.h"
#include "Response.h"

namespace network {

class Packet {
public:
	/**
	 * For zero initialization; don't use directly.
	 */
	Packet()
		: _id(0)
		  , _arrivalTime(0)
		  , _processingDuration(0) {}

	Packet(size_t id, time arrivalTime, duration processingDuration)
		: _id(id)
		  , _arrivalTime(arrivalTime)
		  , _processingDuration(processingDuration) {}

	Packet(const Packet& packet)
		: Packet(packet._id, packet._arrivalTime, packet._processingDuration) {}

	size_t id() const {
		return _id;
	}

	time arrivalTime() const {
		return _arrivalTime;
	}

	duration processingDuration() const {
		return _processingDuration;
	}

	Packet& operator=(Packet&& packet) noexcept {
		_id = packet._id;
		_arrivalTime = packet._arrivalTime;
		_processingDuration = packet._processingDuration;
		return *this;
	}

private:
	size_t _id;
	time _arrivalTime;
	duration _processingDuration;
};

}

#endif //ASSIGNMENT_3__PACKET_H_
