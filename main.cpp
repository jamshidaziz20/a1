#include <iostream>
#include <fstream>
#include <vector>

#include "OpCodes.h"

using namespace std;
int main(int argc, char **argv) {

    // if (argc != 3) {
    //     cout << "Usage: ./dissem objFileName symbolFileName" << endl;
    //     exit(EXIT_FAILURE);
    // }

    // ifstream objFile;

    // vector<string> objData;

    // objFile.open(argv[1], ios::in);

    // string line;

    // while(objFile.good()) {
    //     getline(objFile, line);
    //     objData.push_back(line);
    // }




    // for(int i=0; i < objData.size(); i++) {
    //     cout << objData[i][0] << endl;
    // }


    int threeHalfBytes = 0x031;
    OpCodes *opCodes = new OpCodes;


    cout << "Name: " << opCodes->getSymbolName(threeHalfBytes) << ", Format #" << opCodes->getFormat(threeHalfBytes) << endl;

    

    


}