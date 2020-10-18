//Starter Code:
#include <iostream>
#include <vector>
#include "Packet.h"
#include "Response.h"
#include "Buffer.h"

using namespace std;

std::vector<Packet> readPackets() {
	size_t lineCount;
	std::cin >> lineCount;

	std::vector<Packet> result;
	std::string line;
	for (size_t i = 0; i < lineCount; ++i) {
		std::getline(std::cin, line);
		size_t spaceIndex = line.find(' ');
		if (spaceIndex == std::string::npos) {
			throw std::runtime_error("invalid input");
		}

		auto arivalTime = std::stoull(line.substr(0, spaceIndex));
		auto processingDuration = std::stoull(line.substr(spaceIndex + 1));
		result.push_back(Packet{arivalTime, processingDuration});
	}
	return result;
}

std::vector<Response> processPackets(const std::vector<Packet>& requests, Buffer *pBuffer) {
	return {};
}

void printResponses(const std::vector<Response>& responses) {

}

//please don't modify main function
int main() {
    int bufferSize;
    cin >> bufferSize;
    vector<Packet> requests = readPackets(); //read packets from user

//    //create buffer with the given size
//    Buffer buffer(bufferSize);
//
//    //process the packets
//    vector<Response> responses = processPackets(requests, &buffer);
//
//    //print responses
//    printResponses(responses);

    return 0;
}
