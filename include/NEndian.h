#ifndef NENDIAN_H
#define NENDIAN_H

/// \file NEndian.h
/// implements functions to swap the byte order of several data types
/// to change between Little and Big Endian representation
/// functions can be used to return XXX Endian values from system Endian
/// or read XXX Endian into system Endian variables

#include <cstdint>

namespace NEndian
{
    enum eEndianness { eERROR, eBIG, eLITTLE };
    extern uint8_t endianness;

    void determineEndianness();

    /// return Big Endian representation of 2 bytes
    uint16_t getBigEndian2B(const uint16_t * p);

    /// return Big Endian representation of 4 bytes
    uint32_t getBigEndian4B(const uint32_t * p);

    /// return Big Endian representation of 8 bytes
    uint64_t getBigEndian8B(const uint64_t * p);

    /// return Little Endian representation of 2 bytes
    uint16_t getLittleEndian2B(const uint16_t * p);

    /// return Little Endian representation of 4 bytes
    uint32_t getLittleEndian4B(const uint32_t * p);

    /// return Little Endian representation of 8 bytes
    uint64_t getLittleEndian8B(const uint64_t * p);
}

#endif // NENDIAN_H
