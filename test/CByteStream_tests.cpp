#include <boost/test/unit_test.hpp>

#include "CByteStream.h"

BOOST_AUTO_TEST_SUITE(CByteStream_tests)

BOOST_AUTO_TEST_CASE(CByteStream_uint32_t)
{
    CByteStream byteStream;
    uint32_t x = 0x41424344;
    byteStream << x;
    uint32_t y = 0;
    byteStream >> y;

    BOOST_CHECK_EQUAL(x, y);
}

// TODO: compare strings, other datatypes, ...

BOOST_AUTO_TEST_SUITE_END()
