#pragma once
#include <string>

using namespace std;

class OpCodes
{
    
public:
    string getSymbolName(int threeHalfBytes);
    int getFormat(int threeHalfBytes);
};
