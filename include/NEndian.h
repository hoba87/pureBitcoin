#ifndef NENDIAN_H
#define NENDIAN_H

/// \file NEndian.h
/// implements functions to swap the byte order of several data types
/// to change between Little and Big Endian representation

#include <iostream>
using namespace std;
namespace NEndian
{
    enum eEndianness { ERROR, BIG, LITTLE };
    extern uint8_t endianness;

    void determineEndianness();

    /// swap byte order of 16Bit unsigned int
    uint16_t inline swapByteOrder2B(const uint16_t * p);

    /// swap byte order of 32Bit unsigned int
    uint32_t inline swapByteOrder4B(const uint32_t * p);

    /// swap byte order of 64Bit unsigned int
    uint64_t inline swapByteOrder8B(const uint64_t * p);

    /// return Big Endian representation of 2 bytes
    uint16_t getBigEndian2B(const uint16_t * p);

    /// return Big Endian representation of 4 bytes
    uint32_t getBigEndian4B(const uint32_t * p);

    /// return Big Endian representation of 8 bytes
    uint64_t getBigEndian8B(const uint64_t * p);
}

#endif // NENDIAN_H
