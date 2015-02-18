#include <boost/test/unit_test.hpp>

#include "NEndian.h"
#include "NHash.h"

#include <string>

class CTest
{
public:
    CTest() {
        NEndian::determineEndianness();
    }

    uint8_t hash[32];
    std::string dataInput;

    bool compareHashes(uint8_t h1[32], uint8_t h2[32])
    {
        for(int i = 0; i < 32; i++) {
            if(h1[i] != h2[i]) { return false; }
        }
        return true;
    }
};

BOOST_FIXTURE_TEST_SUITE(NHash_SHA256_tests, CTest)

BOOST_AUTO_TEST_CASE(SHA256_0bytes)
{
    dataInput = "";
    uint8_t hashWithZeroInput[32] = {
        0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
        0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
        0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
        0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
    };

    NHash::SHA256(dataInput.c_str(), dataInput.length(), hash);
    BOOST_CHECK(compareHashes(hash, hashWithZeroInput));
}

BOOST_AUTO_TEST_CASE(SHA256_1_512BitBlock)
{
    dataInput = "abc";
    uint8_t hashWith1BlockInput[32] = {
        0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA,
        0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23,
        0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C,
        0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD
    };
    NHash::SHA256(dataInput.c_str(), dataInput.length(), hash);
    BOOST_CHECK(compareHashes(hash, hashWith1BlockInput));
}

BOOST_AUTO_TEST_CASE(SHA256_2_512BitBlocks)
{
    dataInput = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    uint8_t hashWith2BlockInput[32] = {
        0x24, 0x8D, 0x6A, 0x61, 0xD2, 0x06, 0x38, 0xB8,
        0xE5, 0xC0, 0x26, 0x93, 0x0C, 0x3E, 0x60, 0x39,
        0xA3, 0x3C, 0xE4, 0x59, 0x64, 0xFF, 0x21, 0x67,
        0xF6, 0xEC, 0xED, 0xD4, 0x19, 0xDB, 0x06, 0xC1
    };
    NHash::SHA256(dataInput.c_str(), dataInput.length(), hash);
    BOOST_CHECK(compareHashes(hash, hashWith2BlockInput));
}

BOOST_AUTO_TEST_SUITE_END()
