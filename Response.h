#ifndef ASSIGNMENT_3__RESPONSE_H_
#define ASSIGNMENT_3__RESPONSE_H_

#include <variant>
#include <ostream>
#include <tuple>
#include "time.h" // NOLINT(modernize-deprecated-headers)

namespace network {

/**
 * Packet processing result. Stores dropped status and time when response started processing.
 */
class Response {
public:
	/**
	 * Signifies a dropped packet.
	 */
	struct Dropped {
		bool operator==(const Dropped&) const {
			return true;
		}
	};

	/**
	 * Dropped packet response.
	 */
	static Response newDropped() {
		return Response(0, true);
	}

	/**
	 * Response if packet was processed.
	 */
	static Response newCompletedResponse(time processTime) {
		return Response(processTime, false);
	}

	bool dropped() const {
		return _dropped;
	}

	/**
	 * Check dropped() first.
	 * @return Time when processing started
	 */
	time processTime() const {
		return _processTime;
	}

	/**
	 * UI output.
	 */
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
	explicit Response(time processTime, bool dropped)
		: _processTime(processTime)
		, _dropped(dropped) {}

	time _processTime;
	bool _dropped;
};

}

#endif //ASSIGNMENT_3__RESPONSE_H_
