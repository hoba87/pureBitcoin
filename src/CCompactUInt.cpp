#include "CCompactUInt.h"

#include "NEndian.h"

CCompactUInt::CCompactUInt(uint64_t uint)
{
    this->uint = uint;
}

CCompactUInt::~CCompactUInt()
{

}

uint64_t CCompactUInt::value() const
{
    return uint;
}

unsigned int CCompactUInt::byteLength() const
{
    if(uint <= 252) {
        return 1;
    }
    else if(uint <= 0xFFFF) {
        return 3;
    }
    else if(uint <= 0xFFFFFFFF) {
        return 5;
    }
    else {
        return 9;
    }
}

CByteStream & operator << (CByteStream & byteStream, const CCompactUInt & uInt)
{
    if(uInt.value() <= 252) {
        byteStream << (uint8_t)uInt.uint;
    }
    else {
        if(uInt.value() <= 0xFFFF) {
            uint16_t i = NEndian::getLittleEndian2B((uint16_t*)&uInt.uint);
            byteStream << (uint8_t)253 << i;
        }
        else if(uInt.value() <= 0xFFFFFFFF) {
            uint32_t i = NEndian::getLittleEndian4B((uint32_t*)&uInt.uint);
            byteStream << (uint8_t)254 << i;
        }
        else {
            uint64_t i = NEndian::getLittleEndian8B((uint64_t*)&uInt.uint);
            byteStream << (uint8_t)255 << i;
        }
    }

    return byteStream;
}

CByteStream & operator >> (CByteStream & byteStream, CCompactUInt & uInt)
{
    uint8_t i;
    byteStream >> i;
    if(i <= 252) {
        uInt.uint = i;
    }
    else {
        if(i == 253) {
            uint16_t j;
            byteStream >> j;
            uInt.uint = NEndian::getLittleEndian2B(&j);
        }
        else if(i == 254) {
            uint32_t j;
            byteStream >> j;
            uInt.uint = NEndian::getLittleEndian4B(&j);
        }
        else {
            uint64_t j;
            byteStream >> j;
            uInt.uint = NEndian::getLittleEndian8B(&j);
        }
    }

    return byteStream;
}
