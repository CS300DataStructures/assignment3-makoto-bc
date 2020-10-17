//Starter Code:
#include <iostream>
#include "Packet.h"
#include "Response.h"
#include "Buffer.h"

using namespace std;

//…

//please don't modify main function
int main() {
    int bufferSize;
    cin >> bufferSize;
    vector<Packet> requests = readPackets(); //read packets from user

    //create buffer with the given size
    Buffer buffer(size);

    //process the packets
    vector<Response> responses = processPackets(requests, &buffer);

    //print responses
    printResponses(responses);

    return 0;
}
