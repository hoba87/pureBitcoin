#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#include "NEndian.h"
#include "CNetwork.h"

CNetwork * network;

void init()
{
    NEndian::determineEndianness();

    network = new CNetwork("testnet");
}

int main(int argc, char ** argv)
{
    init();

    thread networkThread(&CNetwork::run, network);

    this_thread::sleep_for(chrono::seconds(3));
    network->shutdown();
    networkThread.join();

    cout << "Hello world!" << endl;

    return 0;
}

