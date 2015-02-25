#include "NEndian.h"

uint8_t NEndian::endianness;

void NEndian::determineEndianness()
{
    endianness = ERROR;
    const uint32_t endianTestUInt32 = 0x4F8EACFB;
    uint8_t * pEndianTestUInt8P = (uint8_t *) & endianTestUInt32;

    if((pEndianTestUInt8P[0] == 0xFB) &&
        (pEndianTestUInt8P[1] == 0xAC) &&
        (pEndianTestUInt8P[2] == 0x8E) &&
        (pEndianTestUInt8P[3] == 0x4F))
    {
        endianness = LITTLE;
    }
    else if((pEndianTestUInt8P[0] == 0x4F) &&
            (pEndianTestUInt8P[1] == 0x8E) &&
            (pEndianTestUInt8P[2] == 0xAC) &&
            (pEndianTestUInt8P[3] == 0xFB))
    {
        endianness = BIG;
    }
}

/// swap byte order of 16Bit unsigned int
uint16_t inline swapByteOrder2B(const uint16_t * p)
{
    return (*p & 0x00FF) << 8 | (*p & 0xFF00) >> 8;
}

/// swap byte order of 32Bit unsigned int
uint32_t inline swapByteOrder4B(const uint32_t * p)
{
    return (*p & 0x000000FF) << 24 | (*p & 0xFF000000) >> 24 |
           (*p & 0x0000FF00) <<  8 | (*p & 0x00FF0000) >>  8;
}

/// swap byte order of 64Bit unsigned int
uint64_t inline swapByteOrder8B(const uint64_t * p)
{
    return (*p & 0x00000000000000FF) << 56 | (*p & 0xFF00000000000000) >> 56 |
           (*p & 0x000000000000FF00) << 40 | (*p & 0x00FF000000000000) >> 40 |
           (*p & 0x0000000000FF0000) << 24 | (*p & 0x0000FF0000000000) >> 24 |
           (*p & 0x00000000FF000000) <<  8 | (*p & 0x000000FF00000000) >>  8;
}

uint16_t NEndian::getBigEndian2B(const uint16_t * p)
{
    if(endianness == LITTLE) {
        return swapByteOrder2B(p);
    }
    else if(endianness == BIG) {
        return *p;
    }
    return 0;
}

uint32_t NEndian::getBigEndian4B(const uint32_t * p)
{
    if(endianness == LITTLE) {
        return swapByteOrder4B(p);
    }
    else if(endianness == BIG) {
        return *p;
    }
    return 0;
}

uint64_t NEndian::getBigEndian8B(const uint64_t * p)
{
    if(endianness == LITTLE) {
        return swapByteOrder8B(p);
    }
    else if(endianness == BIG) {
        return *p;
    }
    return 0;
}

uint16_t NEndian::getLittleEndian2B(const uint16_t * p)
{
    if(endianness == LITTLE) {
        return *p;
    }
    else if(endianness == BIG) {
        return swapByteOrder2B(p);
    }
    return 0;
}

uint32_t NEndian::getLittleEndian4B(const uint32_t * p)
{
    if(endianness == LITTLE) {
        return *p;
    }
    else if(endianness == BIG) {
        return swapByteOrder4B(p);
    }
    return 0;
}

uint64_t NEndian::getLittleEndian8B(const uint64_t * p)
{
    if(endianness == LITTLE) {
        return *p;
    }
    else if(endianness == BIG) {
        return swapByteOrder8B(p);
    }
    return 0;
}
