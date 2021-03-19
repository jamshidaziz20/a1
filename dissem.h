
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "OpCodes.h"

using namespace std;
class dissem
{
private:
      //variables
    int currentAddress;
    vector<string> objData;
    OpCodes *opCodes;

    //methods
    void headRecordAnalyzer(int row);
    void textRecordAnalyzer(int row);
    void endRecordAnalyzer(int row);
    void analyzeFormat2(int objCode);
    void analyzeFormat3(int objCode);
    void analyzeFormat4(int objCode);
public:
    dissem();
    dissem(string fileName);
    ~dissem();
};

dissem::~dissem()
{
}

