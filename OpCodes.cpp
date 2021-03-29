// Developed by 
// Name: Jamshid Aziz   ID:  821340982 
// Name Chance Daily    ID:  821689902

#include "OpCodes.h"
#define size 59
struct opCode {
    string name;
    int opCode;
    bool isFormat2;
};


//only contains directives for formats 2,3, and 4
const struct opCode allOpCodes[] = {
    {"ADD",0x18,false},   {"ADDF",0x58,false},  {"ADDR",0x90,true},   {"AND",0x40,false},   {"CLEAR",0xB4,true}, {"COMP",0x28,false},
    {"COMPF",0x88,false}, {"COMPR",0xA0,true},  {"DIV",0x24,false},   {"DIVF",0x64,false},  {"DIVR",0x9C,true},   {"FIX",0xC4,false},
    {"FLOAT",0xC0,false}, {"HIO",0xF4,false},   {"J",0x3C,false},     {"JEQ",0x30,false},   {"JGT",0x34,false},   {"JLT",0x38,false},
    {"JSUB",0x48,false},  {"LDA",0x00,false},   {"LDB",0x68,false},   {"LDCH",0x50,false},  {"LDF",0x70,false},   {"LDL",0x08,false},
    {"LDS",0x6C,false},   {"LDT",0x74,false},   {"LDX",0x04,false},   {"LPS",0xD0,false},   {"MUL",0x20,false},   {"MULF",0x60,false},
    {"MULR",0x98,true},   {"NORM",0xC8,false},  {"OR",0x44,false},    {"RD",0xD8,false},    {"RMO",0xAC,true},    {"RSUB",0x4C,false},
    {"SHIFTL",0xA4,true}, {"SHIFTR",0xA8,true}, {"SIO",0xF0,false},   {"SSK",0xEC,false},   {"STA",0x0C,false},   {"STB",0x78,false},
    {"STCH",0x54,false},  {"STF",0x80,false},   {"STI",0xD4,false},   {"STL",0x14,false},   {"STS",0x7C,false},   {"STSW",0xE8,false},
    {"STT",0x84,false},   {"STX",0x10,false},   {"SUB",0x1C,false},   {"SUBF",0x5C,false},  {"SUBR",0x94,true},   {"SVC",0xB0,true},
    {"TD",0xE0,false},    {"TIO",0xF8,false},   {"TIX",0x2C,false},   {"TIXR",0xB8,true},   {"WD",0xDC,false},
};

/*
 *  This fucntion recieves a hex value in the form 0x111
 *  Filters out the first six bits and then finds the 
 *  Opcode matching those six bits 
 *  returns the Symbol associated with the first six bits 
*/
string OpCodes::getSymbolName(int threeHalfBytes) {

    int filteredCode = threeHalfBytes & 0xFC0; // 1111 1100 0000<--- AND that with anything will make sure to get first 6 bits
    filteredCode /= 0x10; //truncate the third digit
    int i;
    for(i =0; i<size; i++) {
        if(allOpCodes[i].opCode == filteredCode) {
            return allOpCodes[i].name;
        }
    }
}

/**
 * This function recieves a hex value in the form 0x111
 * First checks if it's format 2
 * Then checks if it's format 3 or 4
 * Finally returns the format number as an integer value
 */
int OpCodes::getFormat(int threeHalfBytes) {

    int filteredCode = threeHalfBytes & 0xFC0; // 1111 1100 0000<--- AND that with anything will make sure to get first 6 bits
    filteredCode /= 0x10; //truncate the third digit

    //first check if it's format 2
    int i;
    for(i=0; i<size; i++) {
        if (allOpCodes[i].opCode == filteredCode
        && allOpCodes[i].isFormat2) return 2;
    }
    
    //check if it's format 3 or 4
    int isFormat4 = threeHalfBytes & 0x001; 
    if(isFormat4) return 4;
    return 3;
}