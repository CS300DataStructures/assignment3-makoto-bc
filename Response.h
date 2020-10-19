#ifndef ASSIGNMENT_3__RESPONSE_H_
#define ASSIGNMENT_3__RESPONSE_H_

#include <variant>
#include "time.h"

namespace network {

struct Dropped {};

class Response {
public:
	static Response newDropped(network::time arrivalTime) {
		return Response(arrivalTime, Dropped{});
	}

	static Response newCompletedResponse(network::time arrivalTime, network::time responseTime) {
		return Response(arrivalTime, responseTime);
	}

private:
	Response(network::time arrivalTime, std::variant<network::time, Dropped> responseTime)
		: _arrivalTime(arrivalTime)
		  , _responseTime(responseTime) {}

	network::time _arrivalTime;
	std::variant<network::time, Dropped> _responseTime;
};

}

#endif //ASSIGNMENT_3__RESPONSE_H_
