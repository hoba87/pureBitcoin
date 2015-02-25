#ifndef CBYTESTREAM_H
#define CBYTESTREAM_H

#include <sstream>

/// \file CByteStream.h

/// \brief implements a binary stringstream
/// by overloading stream operators for several data types
///
/// - overloads of stream operators for compactUInts are implemented here: CCompactUInt
class CByteStream : public std::stringstream
{
    public:
        CByteStream();
        virtual ~CByteStream();
    protected:
    private:
};

/// write string as is to CByteStream
CByteStream & operator << (CByteStream & byteStream, const std::string & str);
/// read string as is from CByteStream
CByteStream & operator >> (CByteStream & byteStream, std::string & str);

/// write other types byte by byte to CByteStream
template <class T>
CByteStream & operator << (CByteStream & byteStream, const T & t)
{
    int size = sizeof(T);
    uint8_t * pT = (uint8_t *)&t;
    for(int i = 0; i < size; i++) {
        static_cast<std::stringstream&>(byteStream) << pT[i];
    }
    return byteStream;
}
/// read other types byte by byte from CByteStream
template <class T>
CByteStream & operator >> (CByteStream & byteStream, T & t)
{
    int size = sizeof(T);
    uint8_t * pT = (uint8_t *)&t;
    for(int i = 0; i < size; i++) {
        static_cast<std::stringstream&>(byteStream) >> pT[i];
    }
    return byteStream;
}

#endif // CBYTESTREAM_H
