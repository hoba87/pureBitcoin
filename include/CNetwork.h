#ifndef CNETWORK_H
#define CNETWORK_H

#include <string>
#include <cstdint>

///////////////////
/// \brief CNetwork
/// handles network communication
///////////////////
class CNetwork
{
    public:
        CNetwork(std::string net);
        virtual ~CNetwork();

        void run();
        void shutdown();

        uint16_t getPort() const;
        uint32_t getMessageHeader() const;
        uint32_t getMaxNBits() const;

    private:
        bool keepRunning;

        uint16_t port;
        uint32_t messageHeader;
        uint32_t maxNBits;

        void initNetParams(std::string net);
        void initMainNet();
        void initTestNet();

        void initSeedNodes();
};

#endif // CNETWORK_H
