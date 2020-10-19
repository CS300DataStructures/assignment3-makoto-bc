#ifndef ASSIGNMENT_3__PACKET_H_
#define ASSIGNMENT_3__PACKET_H_

#include "time.h" // NOLINT(modernize-deprecated-headers)
#include "Response.h"

namespace network {

/**
 * Packets to be processed.
 */
class Packet {
public:
	/**
	 * For default initialization; don't use directly.
	 */
	Packet()
		: _id(0)
		  , _arrivalTime(0)
		  , _processingDuration(0) {}

	Packet(size_t id, time arrivalTime, duration processingDuration)
		: _id(id)
		  , _arrivalTime(arrivalTime)
		  , _processingDuration(processingDuration) {}

	size_t id() const {
		return _id;
	}

	time arrivalTime() const {
		return _arrivalTime;
	}

	duration processingDuration() const {
		return _processingDuration;
	}

private:
	size_t _id;
	time _arrivalTime;
	duration _processingDuration;
};

}

#endif //ASSIGNMENT_3__PACKET_H_
