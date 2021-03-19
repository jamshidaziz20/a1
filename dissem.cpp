

#include "dissem.h"

//They couldn't be members of dissem class, so I put them here
ifstream objFile;
ifstream symbolFile;
ofstream outputFile;

using namespace std;
int main(int argc, char **argv) {

    //checking for command line arguments
    if (argc != 3) {
        cout << "Usage: ./dissem objFileName symbolFileName" << endl;
        exit(EXIT_FAILURE);
    }
   dissem *dissasembler = new dissem(argv[1]); //argv[1] name of object file

}

//Default Constructor for initializing variables
dissem::dissem() {
    opCodes = new OpCodes;
}

dissem::dissem(string fileName){

    objFile.open(fileName, ios::in);
    //checking if file is open
    if(!objFile.is_open()) {
        cout << "Object file not found" << endl;
        exit(EXIT_FAILURE);
    }

    string temp;
    //Store object code data into 2D array
    while(objFile.good()) {
        getline(objFile, temp);
        objData.push_back(temp);
    }

    for(int i=0; i < objData.size(); i++) {
        if(objData[i][0] == 'H'){
            headRecordAnalyzer(i);
        } else if (objData[i][0] == 'T'){
            textRecordAnalyzer(i);
        } else if (objData[i][0] == 'E'){
            endRecordAnalyzer(i);
        }
        
    }

}

void dissem::headRecordAnalyzer(int row) {
    cout << "In Head Record" << endl;
}

void dissem::textRecordAnalyzer(int row) {
    cout << "In Text Recrod" << endl;
}

void dissem::endRecordAnalyzer(int row) {
    cout << "In End Record" << endl;
}


void dissem::analyzeFormat2(int objCode){

}

void dissem::analyzeFormat3(int objCode) {

}

void dissem::analyzeFormat4(int objCode) {

}