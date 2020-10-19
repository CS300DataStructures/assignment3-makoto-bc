#ifndef ASSIGNMENT_3__PACKET_H_
#define ASSIGNMENT_3__PACKET_H_

#include "time.h"
#include "Response.h"

namespace network {

class Packet {
public:
	Packet(size_t id, time arrivalTime, network::duration processingDuration)
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

	network::duration processingDuration() const {
		return _processingDuration;
	}

	Packet& operator=(Packet&& packet) noexcept {
		_arrivalTime = packet._arrivalTime;
		_processingDuration = packet._processingDuration;
		return *this;
	}

private:
	size_t _id;
	network::time _arrivalTime;
	network::duration _processingDuration;
};

}

#endif //ASSIGNMENT_3__PACKET_H_
