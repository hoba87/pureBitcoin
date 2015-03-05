#include "CIP6.h"

CIP6::CIP6(uint8_t ip6[16])
{
    for(int i = 0; i < 16; i++) {
        bytes[i] = ip6[i];
    }
}

CIP6::CIP6()
{
    for(int i = 0; i < 16; i++) {
        bytes[i] = 0;
    }
}

CIP6::~CIP6()
{
    //dtor
}

CIP6 & CIP6::operator = (const CIP6 & ip6)
{
    for(int i = 0; i < 16; i++) {
        this->bytes[i] = ip6.bytes[i];
    }
}

/// writes CIP6 to CByteStream
CByteStream & operator << (CByteStream & byteStream, const CIP6 & ip6)
{
    for(int i = 0; i < 16; i++) {
        byteStream << ip6.bytes[i];
    }
    return byteStream;
}

/// reads CIP6 from CByteStream
CByteStream & operator >> (CByteStream & byteStream, CIP6 & ip6)
{
    for(int i = 0; i < 16; i++) {
        byteStream >> ip6.bytes[i];
    }
    return byteStream;
}
