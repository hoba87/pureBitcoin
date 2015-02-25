#include <boost/test/unit_test.hpp>

#include "CCompactUInt.h"
#include "NEndian.h"

#include <fstream>
using std::fstream;
using std::ios_base;

class CTest
{
public:
    CTest() : uintTemp(0)
    {
        NEndian::determineEndianness();
    }

    ~CTest() {}

    CCompactUInt uintTemp;
    CByteStream byteStream;
};

BOOST_FIXTURE_TEST_SUITE(CCompactUInt_tests, CTest)

BOOST_AUTO_TEST_CASE(CCompactUInt_1byte1)
{
    CCompactUInt uint(123);
    byteStream << uint;
    byteStream >> uintTemp;

    BOOST_CHECK_EQUAL(uintTemp.value(), 123);
}

BOOST_AUTO_TEST_CASE(CCompactUInt_1byte2)
{
    CCompactUInt uint(252);
    byteStream << uint;
    byteStream >> uintTemp;

    BOOST_CHECK_EQUAL(uintTemp.value(), 252);
}

BOOST_AUTO_TEST_CASE(CCompactUInt_2byte)
{
    CCompactUInt uint(0xfedc);
    byteStream << uint;
    byteStream >> uintTemp;

    BOOST_CHECK_EQUAL(uintTemp.value(), 0xfedc);
}

BOOST_AUTO_TEST_CASE(CCompactUInt_4byte)
{
    CCompactUInt uint(0xabcdef);
    byteStream << uint;
    byteStream >> uintTemp;

    BOOST_CHECK_EQUAL(uintTemp.value(), 0xabcdef);
}

BOOST_AUTO_TEST_CASE(CCompactUInt_8byte)
{
    CCompactUInt uint(0xfedcba9876543210);
    byteStream << uint;
    byteStream >> uintTemp;

    BOOST_CHECK_EQUAL(uintTemp.value(), 0xfedcba9876543210);
}

BOOST_AUTO_TEST_SUITE_END()
