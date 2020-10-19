#ifndef ASSIGNMENT_3__PACKET_H_
#define ASSIGNMENT_3__PACKET_H_

#include "time.h"
#include "Response.h"

class Packet {
public:
	time::time arrivalTime;
	time::duration processingDuration;
};

#endif //ASSIGNMENT_3__PACKET_H_
