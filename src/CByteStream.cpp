#include "CByteStream.h"

CByteStream::CByteStream()
{

}

CByteStream::~CByteStream()
{

}

CByteStream & operator << (CByteStream & byteStream, const std::string & str)
{
    static_cast<std::stringstream&>(byteStream) << str;
    return byteStream;
}

CByteStream & operator >> (CByteStream & byteStream, std::string & str)
{
    static_cast<std::stringstream&>(byteStream) >> str;
    return byteStream;
}
