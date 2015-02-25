#ifndef CBYTESTREAM_H
#define CBYTESTREAM_H

#include <sstream>

/// implements a binary stringstream
class CByteStream : public std::stringstream
{
    public:
        CByteStream();
        virtual ~CByteStream();
    protected:
    private:
};

/// write string as is to bytestream
CByteStream & operator << (CByteStream & byteStream, const std::string & str);

/// write other types byte by byte to stream
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

/// read string as is from bytestream
CByteStream & operator >> (CByteStream & byteStream, std::string & str);

/// read other types byte by byte from stream
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
