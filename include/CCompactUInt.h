#ifndef CCOMPACTUINT_H
#define CCOMPACTUINT_H

#include <cstdint>
class CByteStream;

/// \brief implements the representation of an unsigned int with variable size of 1, 1+2, 1+4 or 1+8 bytes,
/// the maximum value which can be represented is 2^64-1
///
/// format:
/// - x <= 252    ->       1 byte value
/// - x <= 2^16-1 -> 0xFD, followed by 2 bytes value, Little Endian
/// - x <= 2^32-1 -> 0xFE, followed by 4 bytes value, Little Endian
/// - x <= 2^64-1 -> 0xFF, followed by 8 bytes value, Little Endian
class CCompactUInt
{
    public:
        CCompactUInt(uint64_t uint);
        virtual ~CCompactUInt();

        /// return value of CCompactUInt as uint64_t
        uint64_t value() const;
        /// returns the bytes count needed to represent CCompactUInt
        unsigned int byteLength() const;
    protected:
    private:
        uint64_t uint;

        friend CByteStream & operator << (CByteStream &, const CCompactUInt &);
        friend CByteStream & operator >> (CByteStream &, CCompactUInt &);
};

/// writes CCompactUInt to CByteStream
CByteStream & operator << (CByteStream &, const CCompactUInt &);
/// reads CCompactUInt from CByteStream
CByteStream & operator >> (CByteStream &, CCompactUInt &);

#endif // CCOMPACTUINT_H
