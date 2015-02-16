#ifndef SWAPBYTEORDER_H
#define SWAPBYTEORDER_H

/// \file SwapByteOrder.h
/// implements functions to swap the byte order of several data types
/// to change between Little and Big Endian representation

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

#endif // SWAPBYTEORDER_H
