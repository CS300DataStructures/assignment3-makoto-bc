#include <algorithm>
#include <cassert>
#include "Buffer.h"

namespace network {

struct ResponseEntry { // NOLINT(cppcoreguidelines-pro-type-member-init)
	size_t packetID;
	Response response;
};

/**
 * @return Sorted responses
 */
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
	/*
	 * Given input packets of:
	 * 0 2
	 * 1 1
	 * 1 1
	 * 2 1
	 * and a buffer size of 2, this solves the responses by iterating through the inputs:
	 * 0 2 // There is no packet in buffer so add this to buffer.
	 * 1 1 // Packet in buffer is still processing. Add this packet to buffer.
	 * 1 1 // Packet in buffer is still processing. Buffer is full so this is dropped.
	 * 2 1 // 0th packet in buffer is done and is added to response. Add this packet to buffer.
	 * // Buffer is iterated to calculate remaining responses
	 * // Sort responses because dropped packets were added to responses before processed packets
	 * // and the result needs to be sorted by packet order.
	 *
	 * Output is:
	 * 0
	 * 2
	 * -1
	 * 3
	 */

	assert(pBuffer->size() == 0);

	// Time when last packet finished processing
	time lastPacketFinished = 0;
	std::vector<ResponseEntry> responses;
	for (size_t packetIndex = 0; packetIndex < packets.size(); ++packetIndex) {
		if (pBuffer->size() > 0) {
			// Check if 0th packet in buffer is done processing at current packet's arrival time
			time responseTime
				= (*pBuffer)[0].arrivalTime()
					+ (*pBuffer)[0].processingDuration();
			if (responseTime <= packets[packetIndex].arrivalTime()) {
				// Response time is packet arrival or when last packet finished processing, which
				// ever is later
				time processTime = std::max((*pBuffer)[0].arrivalTime(), lastPacketFinished);
				auto response = Response::newCompletedResponse(processTime);
				responses.push_back(ResponseEntry{(*pBuffer)[0].id(), response});
				lastPacketFinished = processTime + (*pBuffer)[0].processingDuration();
				pBuffer->popFront();
			}
		}

		// Attempt to add packet to buffer
		if (pBuffer->pushBack(packets[packetIndex]) == Buffer::PushBackResult::Dropped) {
			responses.push_back(ResponseEntry{packetIndex, Response::newDropped()});
		}
	}

	// Process remaining packets in buffer
	for (size_t i = 0; i < pBuffer->size(); ++i) {
		time processTime = std::max((*pBuffer)[i].arrivalTime(), lastPacketFinished);
		auto response = Response::newCompletedResponse(processTime);
		responses.push_back(ResponseEntry{(*pBuffer)[i].id(), response});
		lastPacketFinished = processTime + (*pBuffer)[i].processingDuration();
	}

	// Sort responses by packet ID
	return responseEntriesToResponses(std::move(responses));
}

}
