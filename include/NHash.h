#ifndef NHASH_H
#define NHASH_H

#include <cstdint>

/// \file NHash.h

/// provides several hash functions
namespace NHash
{
    /// \brief Implements the SHA256 hashing algorithm.
    /// A description of the SHA256 algorithm can be found here:
    /// [FIPS-180-4](http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf)
    ///
    /// @param data pointer to data of any type to calculate hash from
    /// @param length length of data in bytes
    /// @param hash hash calculated by function
    /// @note - process only data which length is a multiple of bytes
    /// @note - slower than implementation in bitcoin core
    void SHA256(const void * data, const uint64_t length, uint8_t hash[32]);

    /// \brief Executes the SHA256 algorithm two times.
    /// @see SHA256
    /// @param data pointer to data of any type to calculate hash from
    /// @param length length of data in bytes
    /// @param hash hash calculated by function
    void SHA256x2(const void * data, const uint64_t length, uint8_t hash[32]);
}

#endif // NHASH_H
