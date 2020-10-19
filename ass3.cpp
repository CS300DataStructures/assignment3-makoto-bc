// assignment-3
// Makoto Emura
// 10/19/2020
// Network packet buffer

#include <iostream>
#include <vector>
#include "Packet.h"
#include "Response.h"
#include "Buffer.h"

namespace network {

/**
 * Reads packets from stdin.
 */
std::vector<Packet> readPackets() {
	// Read number of packets
	size_t lineCount;
	std::cin >> lineCount;
	std::cin.ignore();

	std::vector<Packet> result;
	std::string line;
	for (size_t i = 0; i < lineCount; ++i) {
		// Each line is formatted as: arrivalTime processingDuration
		std::getline(std::cin, line);
		size_t spaceIndex = line.find(' ');
		if (spaceIndex == std::string::npos) {
			throw std::runtime_error("invalid input");
		}

		time arivalTime = std::stoull(line.substr(0, spaceIndex));
		time processingDuration = std::stoull(line.substr(spaceIndex + 1));
		result.emplace_back(i, arivalTime, processingDuration);
	}
	return result;
}

/**
 * Outputs response times. Outputs "-1" if packet was dropped. Outputs "-2" if 0 packets were
 * inputted.
 */
void printResponses(const std::vector<Response>& responses) {
	if (responses.empty()) {
		std::cout << "-2\n";
	}

	for (const Response& response : responses) {
		response.output(std::cout);
		std::cout << '\n';
	}
	std::cout << std::flush;
}

}

using namespace std;
using namespace network;

//please don't modify main function
int main() {
	int bufferSize;
	cin >> bufferSize;
	vector<Packet> requests = readPackets(); //read packets from user

	//create buffer with the given size
	Buffer buffer(bufferSize);

	//process the packets
	vector<Response> responses = processPackets(requests, &buffer);

	//print responses
	printResponses(responses);

	return 0;
}
