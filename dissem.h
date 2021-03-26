#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "OpCodes.h"
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;


class dissem
{
private:
      //variables
    int currentAddress;
    vector<string> objData;
    OpCodes *opCodes;
    map<int,string> symbols; //Address and the associated Symbol 
    map<int, pair<string, int>> literals; //Address and the associated literal
    map<char, int> registers; //Register 

    //methods
    void headRecordAnalyzer(int row);
    void textRecordAnalyzer(int row);
    void endRecordAnalyzer(int row);
    void analyzeFormat2(int objCode, string opName);
    void analyzeFormat3(int objCode, string opName);
    void analyzeFormat4(int objCode, string opName);
public:
    dissem();
    dissem(string objFileName, string symFileName);
    ~dissem();
};

dissem::~dissem()
{
}