#ifndef ASSIGNMENT_3__RESPONSE_H_
#define ASSIGNMENT_3__RESPONSE_H_

#include "time.h"

struct Dropped {};

class Response {
public:
	time::time arrivalTime;
	std::variant<time::time, Dropped> responseTime;
};

#endif //ASSIGNMENT_3__RESPONSE_H_
