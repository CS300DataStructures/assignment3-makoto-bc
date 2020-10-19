#ifndef ASSIGNMENT_3__RESPONSE_H_
#define ASSIGNMENT_3__RESPONSE_H_

#include <variant>
#include <ostream>
#include <tuple>
#include "time.h"

namespace network {

class Response {
public:
	struct Dropped {
		bool operator==(const Dropped& rhs) const {
			return true;
		}
	};

	static Response newDropped() {
		return Response(Dropped{});
	}

	static Response newCompletedResponse(time processTime) {
		return Response(processTime);
	}

	bool dropped() const {
		return std::holds_alternative<Dropped>(_processTime);
	}

	time processTime() const {
		return std::get<time>(_processTime);
	}

	void output(std::ostream& os) const {
		if (dropped()) {
			os << "-1";
		} else {
			os << processTime();
		}
	}

	bool operator==(const Response& rhs) const {
		return std::tie(_processTime, _processTime) == std::tie(rhs._processTime, rhs._processTime);
	}

	friend std::ostream& operator<<(std::ostream& os, const Response& response) {
		if (response.dropped()) {
			os << "dropped";
		} else {
			os << response.processTime();
		}
		return os;
	}

private:
	Response(std::variant<time, Dropped> processTime)
		: _processTime(processTime) {}

	std::variant<time, Dropped> _processTime;
};

}

#endif //ASSIGNMENT_3__RESPONSE_H_
