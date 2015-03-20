#include "CNetwork.h"

#include "NEndian.h"

#include <string>
#include <stdexcept>

const uint16_t mainNetPort =  8333;
const uint16_t testNetPort = 18333;
const uint32_t mainNetMessageHeader = 0xf9beb4d9;
const uint32_t testNetMessageHeader = 0x0b110907;
const uint32_t mainNetMaxNBits = 0x1d00ffff;
const uint32_t testNetMaxNBits = 0x1d00ffff;

CNetwork::CNetwork(std::string net)
{
    keepRunning = true;
    initNetParams(net);

    initSeedNodes();
}

CNetwork::~CNetwork()
{

}

void CNetwork::run()
{
    while(keepRunning) {

    }
}

void CNetwork::shutdown()
{
    keepRunning = false;
}

uint16_t CNetwork::getPort() const
{
    return port;
}

uint32_t CNetwork::getMessageHeader() const
{
    return NEndian::getBigEndian4B(&messageHeader);
}

uint32_t CNetwork::getMaxNBits() const
{
    return maxNBits;
}

void CNetwork::initNetParams(std::string net)
{
    if(net.compare("mainnet") == 0) {
        initMainNet();
    }
    else if(net.compare("testnet") == 0) {
        initTestNet();
    }
    else {
        throw std::invalid_argument("unknown net param");
    }
}

void CNetwork::initMainNet()
{
    port = mainNetPort;
    messageHeader = mainNetMessageHeader;
    maxNBits = mainNetMaxNBits;
}

void CNetwork::initTestNet()
{
    port = testNetPort;
    messageHeader = testNetMessageHeader;
    maxNBits = testNetMaxNBits;
}

void CNetwork::initSeedNodes()
{

}
