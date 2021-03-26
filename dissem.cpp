
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
   dissem *dissasembler = new dissem(argv[1], argv[2]); //argv[1] name of object file

}

dissem::dissem(string objFileName, string symFileName){

    opCodes = new OpCodes;
    objFile.open(objFileName, ios::in);
    symbolFile.open(symFileName, ios::in);
    // outputFile.open("temp.lst", ios::out);

    //checking if file is open
    if(!objFile.is_open() || !symbolFile.is_open() ) {
        cout << "Object or Symbol file not found" << endl;
        exit(EXIT_FAILURE);
    }

    string temp;
    //Read & Store object code data into 2D array
    while(objFile.good()) {
        getline(objFile, temp);
        objData.push_back(temp);
    }

    // //Read & store Symbol table and Ltieral table into maps
    // int counter = 0;
    // while (symbolFile.good()){
    //     getline(symbolFile, temp);

    //     if(temp[0] == 'S' || temp[0]=='-') continue;
    //     if(temp[0]== ' ') break;
    //     cout<< temp << endl;
    // }
    // while (symbolFile.good()){
    //     getline(symbolFile, temp);
    //     if(temp[0] == 'N' || temp[0]=='-') continue;
    //     cout<< temp[1] << endl;
        
    // }
    
    //Traversin through each row in the object file
    for(int i=0; i < objData.size(); i++) {
        if(objData[i][0] == 'H'){
            headRecordAnalyzer(i);
        } else if (objData[i][0] == 'T'){
            if(i==1) currentAddress = stoi(objData[i].substr(1,6),NULL, 16);
            textRecordAnalyzer(i);
        } else if (objData[i][0] == 'E'){
            endRecordAnalyzer(i);
        }
        
    }


    objFile.close();
    symbolFile.close();
}

void dissem::headRecordAnalyzer(int row) {
    //1-6(inlcusive) program name
    //7-12(inclusive) starting address (hex)
    //13-18(inclusive) length of object program in bytes (hex)
    string progName = objData[row].substr(1,6);
    int startAddress = stoi(objData[row].substr(7,6), NULL, 16);
    int lengthInHex = stoi(objData[row].substr(13,6), NULL, 16);

    // cout << "Progname "<< progName <<  " Start Address: "<< hex << startAddress <<" Length: " << hex << lengthInHex << endl;
    
}

void dissem::textRecordAnalyzer(int row) {
    /* Col 1-6 starting address in hex
    *  Col 7-8 Lenght of object code in this record in bytes (hex)
    *  Col 9-68 Object code,
    */
    int startAddress = stoi(objData[row].substr(1,6),NULL, 16);
    int length =  stoi(objData[row].substr(7,2), NULL, 16);

   //If the current address < starting address of the record, then we need to make check symbol table and reserver memory using RESW command 
   //else if Current address is in symbol table then we just need to add label for that line
    if(currentAddress < startAddress) {
        //traverse through the Symbol Tables
        // cout << "Goteeem" << endl;
    }
    //Traversing through the record
    int firstThree, format, objectCode;
    // cout << "row = " << row << endl;
    for(int i = 9; i< (2*length) +9; i++) {
       firstThree = stoi(objData[row].substr(i,3), NULL, 16);
       format = opCodes->getFormat(firstThree);
       objectCode = stoi(objData[row].substr(i,format*2), NULL, 16);

       if (format == 2) {
           analyzeFormat2(objectCode, opCodes->getSymbolName(firstThree));
       } else if (format == 3){
           analyzeFormat3(objectCode, opCodes->getSymbolName(firstThree));

       } else if (format == 4) {
           analyzeFormat4(objectCode, opCodes->getSymbolName(firstThree));

       } else {
           cout << "Unknown Format" << endl;
       }

        // cout << "Current Address: " << setfill('0')<< setw(4) << currentAddress << uppercase<< hex;
        // cout << " Object code: "<< setfill('0') << setw(format*2)<< objectCode << " Format:"<< format<< endl;
        
        currentAddress += format;
        i += format*2-1; //offset to next object code, varies based on current format*2 -> gives half bytes

       
    }
    // cout << "\n" ;


}

void dissem::endRecordAnalyzer(int row) {
}


void dissem::analyzeFormat2(int objCode, string opName){
}

void dissem::analyzeFormat3(int objCode, string opName) {

}

void dissem::analyzeFormat4(int objCode, string opName) {

}