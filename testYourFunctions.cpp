#include <iostream>
#include <fstream>
#include <vector>

#include "OpCodes.h"

using namespace std;
int main(int argc, char **argv) {
    printf("%d", (0x6910083E & 0xFC0000)) >> 18;
}