#ifndef CIP6_H
#define CIP6_H

#include <cstdint>
#include "CByteStream.h"

class CIP6
{
    public:
        CIP6(uint8_t ip6[16]);
        CIP6();
        virtual ~CIP6();

        uint8_t bytes[16];

        CIP6 & operator = (const CIP6 & ip6);
    protected:
    private:
        friend CByteStream & operator << (CByteStream &, const CIP6 &);
        friend CByteStream & operator >> (CByteStream &, CIP6 &);
};

/// writes CIP6 to CByteStream
CByteStream & operator << (CByteStream &, const CIP6 &);
/// reads CIP6 from CByteStream
CByteStream & operator >> (CByteStream &, CIP6 &);

#endif // CIP6_H
