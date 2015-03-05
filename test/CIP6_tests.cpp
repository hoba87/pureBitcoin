#include <boost/test/unit_test.hpp>

#include "CIP6.h"

class CTest
{

};

BOOST_FIXTURE_TEST_SUITE(CIP6_tests, CTest)

BOOST_AUTO_TEST_CASE(eq_operator)
{
    uint8_t ip[16];
    CIP6 ip6_1(ip);
    CIP6 ip6_2 = ip6_1;

    for(int i = 0; i < 16; i++) {
        BOOST_CHECK_EQUAL(ip6_1.bytes[i], ip6_2.bytes[i]);
    }
}

BOOST_AUTO_TEST_CASE(byteStream)
{
    CByteStream byteStream;
    uint8_t x[16];
    x[0]  =  1; x[1]  = 2; x[2]  =   3; x[3]  =  10;
    x[4]  = 13; x[5]  = 0; x[6]  = 255; x[7]  = 200;
    x[8]  = 45; x[9]  = 7; x[10] =  61; x[11] =  92;
    x[12] = 72; x[13] = 9; x[14] =  40; x[15] = 235;
    CIP6 ip6_1(x);
    byteStream << ip6_1;
    CIP6 ip6_2;
    byteStream >> ip6_2;

    for(int i = 0; i < 16; i++) {
        BOOST_CHECK_EQUAL(ip6_1.bytes[i], ip6_2.bytes[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()
