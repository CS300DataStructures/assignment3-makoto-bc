#include <algorithm>
#include <cassert>
#include "Buffer.h"

namespace network {

struct ResponseEntry { // NOLINT(cppcoreguidelines-pro-type-member-init)
	size_t packetID;
	Response response;
};

std::vector<Response> responseEntriesToResponses(std::vector<ResponseEntry> responses) {
	std::sort(responses.begin(), responses.end(), [](const auto& a, const auto& b) {
		return a.packetID < b.packetID;
	});

	std::vector<Response> result;
	result.reserve(responses.size());
	for (const auto& entry : responses) {
		result.push_back(entry.response);
	}
	return result;
}

std::vector<Response> processPackets(const std::vector<Packet>& packets, Buffer* pBuffer) {
	assert(pBuffer->size() == 0);

	std::vector<ResponseEntry> responses;
	time lastPacketFinished = 0;
	for (size_t packetIndex = 0; packetIndex < packets.size(); ++packetIndex) {
		if (pBuffer->size() > 0) {
			time responseTime
				= (*pBuffer)[0].arrivalTime()
					+ (*pBuffer)[0].processingDuration();
			if (responseTime <= packets[packetIndex].arrivalTime()) {
				time processTime = std::max((*pBuffer)[0].arrivalTime(), lastPacketFinished);
				auto response = Response::newCompletedResponse(processTime);
				responses.push_back(ResponseEntry{(*pBuffer)[0].id(), response});
				lastPacketFinished = processTime + (*pBuffer)[0].processingDuration();
				pBuffer->popFront();
			}
		}

		if (pBuffer->pushBack(packets[packetIndex]) == Buffer::PushBackResult::Dropped) {
			auto response = Response::newDropped();
			responses.push_back(ResponseEntry{packetIndex, response});
		}
	}

	for (size_t i = 0; i < pBuffer->size(); ++i) {
		time processTime = std::max((*pBuffer)[i].arrivalTime(), lastPacketFinished);
		auto response = Response::newCompletedResponse(processTime);
		responses.push_back(ResponseEntry{(*pBuffer)[i].id(), response});
		lastPacketFinished = processTime + (*pBuffer)[i].processingDuration();
	}

	return responseEntriesToResponses(std::move(responses));
}

}
