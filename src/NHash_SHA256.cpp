#include "NHash.h"

#include <cstring>

// swap byte order of 32Bit data type
uint32_t inline getBigEndian32(const uint32_t * p)
{
    return (*p & 0x000000FF) << 24 | (*p & 0xFF000000) >> 24 |
           (*p & 0x0000FF00) <<  8 | (*p & 0x00FF0000) >>  8;
}

// swap byte order of 64Bit data type
uint64_t inline getBigEndian64(const uint64_t * p)
{
    return (*p & 0x00000000000000FF) << 56 | (*p & 0xFF00000000000000) >> 56 |
           (*p & 0x000000000000FF00) << 40 | (*p & 0x00FF000000000000) >> 40 |
           (*p & 0x0000000000FF0000) << 24 | (*p & 0x0000FF0000000000) >> 24 |
           (*p & 0x00000000FF000000) <<  8 | (*p & 0x000000FF00000000) >>  8;
}

// fips-180-4.pdf (4.1.2)
uint32_t inline  Ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
uint32_t inline Maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
uint32_t inline Sigma0(uint32_t x) { return (x >>  2 | x << 30) ^ (x >> 13 | x << 19) ^ (x >> 22 | x << 10); }
uint32_t inline Sigma1(uint32_t x) { return (x >>  6 | x << 26) ^ (x >> 11 | x << 21) ^ (x >> 25 | x <<  7); }
uint32_t inline sigma0(uint32_t x) { return (x >>  7 | x << 25) ^ (x >> 18 | x << 14) ^ (x >>  3); }
uint32_t inline sigma1(uint32_t x) { return (x >> 17 | x << 15) ^ (x >> 19 | x << 13) ^ (x >> 10); }

// fips-180-4.pdf (4.2.2)
const uint32_t SHA256Constants[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// fips-180-4.pdf (6.2.2)
void processMessageBlock(const void * pDataBlock, uint32_t * H)
{
    uint32_t * p32DataBlock = (uint32_t *)pDataBlock;
    uint32_t W[64];
    uint32_t a, b, c, d, e, f, g, h;

    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    for(uint32_t t = 0; t < 16; t++) {
        W[t] = getBigEndian32(p32DataBlock + t);
    }
    for(uint32_t t = 16; t < 64; t++) {
        W[t] = sigma1(W[t - 2]) + W[t - 7] + sigma0(W[t - 15]) + W[t - 16];
    }
    for(uint32_t t = 0; t < 64; t++) {
        uint32_t T1, T2;
        T1 = h + Sigma1(e) + Ch(e, f, g) + SHA256Constants[t] + W[t];
        T2 = Sigma0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
}

void NHash::SHA256(const void * data, const uint64_t length, uint8_t hash[32])
{
    uint8_t * dataBytes = (uint8_t *)data;

    // initialize hash
    uint32_t H[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // process full 512 Bit blocks
    uint64_t nFull512BitBlocks = length / 64;
    for(uint64_t n = 0; n < nFull512BitBlocks * 64; n += 64) {
        processMessageBlock(dataBytes + n, &H[0]);
    }

    // process last bytes (remaining one or two 512 Bit blocks)
    uint32_t nLastDataBytes    = length % 64;
    uint32_t nPadBytes         = (64 - nLastDataBytes);
    if(nPadBytes < (8 + 1)) { nPadBytes += 64; }
    uint32_t nRemainingBytes   = nLastDataBytes + nPadBytes;
    uint8_t * lastBlocks       = new uint8_t[nRemainingBytes];

    // copy last data bytes
    memcpy(lastBlocks, dataBytes + nFull512BitBlocks * 64, nLastDataBytes);
    // padding starts with 10000000...
    lastBlocks[nLastDataBytes] = 0x80;
    // ... followed by zeros ...
    for(uint8_t n = (nLastDataBytes + 1); n < (nRemainingBytes - 8); n++) {
        lastBlocks[n] = 0x00;
    }
    // ... and by length in bit
    uint64_t nLengthInBits          = length * 8;
    uint64_t nLengthInBitsBigEndian = getBigEndian64(&nLengthInBits);
    memcpy(&lastBlocks[nRemainingBytes - 8], &nLengthInBitsBigEndian, 8);
    // process blocks
    for(uint8_t n = 0; n < nRemainingBytes; n += 64) {
        processMessageBlock(&lastBlocks[n], &H[0]);
    }
    delete[] lastBlocks;

    // copy hash value
    for(uint8_t n = 0; n < 8; n++) {
        uint32_t h = getBigEndian32(&H[n]);
        memcpy(&hash[n * 4], &h, 4);
    }
}

void NHash::SHA256x2(const void * data, const uint64_t length, uint8_t hash[32])
{
    SHA256(data, length, hash);
    SHA256(hash, 32, hash);
}
