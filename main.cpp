#include <iostream>
using namespace std;

#include "NEndian.h"
#include "NHash.h"

void init()
{
    NEndian::determineEndianness();
}

int main()
{
    init();

    cout << "Hello world!" << endl;

    return 0;
}

