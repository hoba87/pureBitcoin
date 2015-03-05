#include "CByteStream.h"

CByteStream::CByteStream()
{

}

CByteStream::~CByteStream()
{

}

const unsigned char * CByteStream::cstr()
{
    return (const unsigned char *)this->str().c_str();
}

unsigned int CByteStream::length()
{
    return this->str().length();
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
