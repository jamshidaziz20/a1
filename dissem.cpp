// Developed by 
// Name: Jamshid Aziz   ID:  821340982 
// Name Chance Daily    ID:  821689902


#include "dissem.h"

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


/*
 * This function recieves 2 files names
 * The object file name, and the symbol file name
 * Opens the files & stores the data in objData, symbols, literals respectively
 * Traverses through each record in the object file & calls either 
 * Head/Text/End record analyzer functions, which recieve the row index
 * Close files when done
*/
dissem::dissem(string objFileName, string symFileName){
    
    ifstream objFile;
    ifstream symbolFile;
    regValue.insert(pair<char,int>('A', 0));
    regValue.insert(pair<char,int>('X', 0));
    regValue.insert(pair<char,int>('L', 0));
    regValue.insert(pair<char,int>('B', 0));
    regValue.insert(pair<char,int>('S', 0));
    regValue.insert(pair<char,int>('T', 0));
    regValue.insert(pair<char,int>('F', 0));
    opCodes = new OpCodes;
    objFile.open(objFileName, ios::in);
    symbolFile.open(symFileName, ios::in);
    outputFile.open("temp.lst", ios::out);

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

    //Read & store Symbol table and Ltieral table into maps
    int counter = 0;
    string arr[3];
    while (symbolFile.good()){
        getline(symbolFile, temp);

        if(temp[0] == 'S' || temp[0]=='-') continue;
        if(temp.size() == 0) break;


        //using this to split string by space
        istringstream ss(temp);
        
        while(ss.good() && counter <2) {
            ss >> arr[counter];
            counter++;
        }
        symbols[stoi(arr[1], NULL, 16)] = arr[0];
        counter = 0;
    }

    while (symbolFile.good()){
        getline(symbolFile, temp);
        if(temp[0] == 'N' || temp[0]=='-') continue;
        
        istringstream ss(temp);

        while(ss.good() & counter <3) {
            ss >> arr[counter];
            counter++;
        }
        literals[stoi(arr[2], NULL, 16)] = pair<string,int>(arr[0], stoi(arr[1]));
        counter = 0;
    }

    
    // Traversin through each row in the object file
    
    for(int i=0; i < objData.size(); i++) {
        if(objData[i][0] == 'H'){
            currentAddress = stoi(objData[i].substr(7,6),NULL, 16);
            headRecordAnalyzer(i);
        } else if (objData[i][0] == 'T'){
            textRecordAnalyzer(i);
        } else if (objData[i][0] == 'E'){
            endRecordAnalyzer(i);
        }
        
    }

    /* for(map<char, int >::const_iterator it = regValue.begin();
             it != regValue.end(); ++it)
                {
                std::cout << it->first << " " << it->second<< "\n";
                }*/
    /*registers[1]='A';
    registers[2]='X';
    registers[3]='L';
    registers[4]='B';
    registers[5]='S';
    registers[6]='T';
    registers[7]='F';*/
    objFile.close();
    symbolFile.close();
    outputFile.close();
}


void dissem::headRecordAnalyzer(int row) {
    //1-6(inlcusive) program name
    //7-12(inclusive) starting address (hex)
    //13-18(inclusive) length of object program in bytes (hex)
    string progName = objData[row].substr(1,6);
    int startAddress = stoi(objData[row].substr(7,6), NULL, 16);
    int lengthInHex = stoi(objData[row].substr(13,6), NULL, 16);

     outputFile << setfill('0')<< setw(4)  << uppercase << hex << currentAddress  
            << setfill(' ')<< "\t\t" << progName
            << "\t\t\t\t" <<  "START" << "\t\t\t" << 0<< endl ;
    
}


/*
 * This function traverses through each object code & calls the 
 * function accoridng to it's format 2/3/4
 * It's responsible for writing to output file the following:
 * Current Address, the symbol names, reserving buffer, 
 * And defining the literals 
*/
void dissem::textRecordAnalyzer(int row) {
    /* Col 1-6 starting address in hex
    *  Col 7-8 Lenght of object code in this record in bytes (hex)
    *  Col 9-68 Object code,
    */

    //The key is the amount of space in bytes (hex), the value is the name of Symbol
    vector<pair<int, string>> bytesPerSymbol;
    int startAddress = stoi(objData[row].substr(1,6),NULL, 16);
    int length =  stoi(objData[row].substr(7,2), NULL, 16);

   //Reserve memory when ther is a gap
    if(currentAddress < startAddress) {


        int capacity = startAddress - currentAddress;

        //Getting to the symbol that starts with the current address
        auto itter = symbols.begin();
        while(itter->first != currentAddress ) itter++;

        string symbolName = itter->second;
        //if more symbols exist
        int curr = itter->first;
        if(++itter != symbols.end()){

            
            int next = itter->first;

            //Calculating how much storage per Symbol
            do {
                bytesPerSymbol.push_back(pair<int, string>(next-curr,symbolName));
                capacity -= (next-curr);
                symbolName = itter ->second;
                itter++;//Go to next symbol
                curr = next;
                next = itter->first;
            } while (next-curr < capacity && itter != symbols.end());

            if(capacity > 0) {
                bytesPerSymbol.push_back(pair<int, string>(capacity,symbolName));
            }

        } else {
            //If reserving memory only for one symbol
            bytesPerSymbol.push_back(pair<int, string>(capacity,symbolName));
        }

        // Write to file
        for (auto itter = bytesPerSymbol.begin(); itter != bytesPerSymbol.end(); itter++){
            
        outputFile << setfill('0')<< setw(4)  << uppercase << hex << currentAddress  
            << setfill(' ')<< "\t\t" << itter->second
            << "\t" << "RESW\t\t\t" << dec << itter->first/3 <<endl ;

        currentAddress += itter->first;

        }
        
        //Print structure: Address    Label      RESW    amount in decimal   
    }


    //Traversing through the record
    int firstThree, format, objectCode;
    string opCodeName;
    // cout << "row = " << row << endl;
    for(int i = 9; i< (2*length) +9; i++) {
       firstThree = stoi(objData[row].substr(i,3), NULL, 16);
       format = opCodes->getFormat(firstThree);
       opCodeName = opCodes->getSymbolName(firstThree);
       //printf("opCodeName is: %s\n",opCodeName);
       objectCode = stoi(objData[row].substr(i,format*2), NULL, 16);
       bool literalsExist = literals.count(currentAddress) > 0; 
       bool symbolsExist = symbols.count(currentAddress) > 0;

        //Writing the address to the file
        

       //checking if literals exist in the current address
       if(literalsExist){
           outputFile << "\t\t\tLTORG\n"; 
            outputFile << setfill('0')<< setw(4)  << uppercase << hex << currentAddress;
           int length = literals[currentAddress].second;
           int value = stoi(literals[currentAddress].first.substr(3,length), NULL, 16); //removes the =x'' part
           string literal = literals[currentAddress].first;
           
           outputFile << "\t\t\t" << "*\t\t\t" << literal << "\t\t\t" << uppercase << hex << setfill('0') << setw(length)<< value;

           //Sample: 0855              *       =X'000001'      000001

       } 
       else{
           outputFile << setfill('0')<< setw(4)  << uppercase << hex << currentAddress;
       }

       //if the address exists in the symbol table print the symbol name
        if(symbolsExist) {
            outputFile << "\t\t" << symbols[currentAddress];
        }       
       
       if(!literalsExist){
        if (format == 2)         analyzeFormat2(objectCode,opCodeName);
        else if (format == 3)    analyzeFormat3(objectCode,opCodeName);
        else if (format == 4)    analyzeFormat4(objectCode,opCodeName);
        else                     cout << "Unknown Format" << endl;
       }

       
        // Debug purposes
        // cout << "Current Address: " << setfill('0')<< setw(4) << currentAddress << uppercase<< hex;
        // cout << " Object code: "<< setfill('0') << setw(format*2)<< objectCode << " Format:"<< format<< endl;
        
        currentAddress += format;
        i += format*2-1; //offset to next object code, varies based on current format*2 -> gives half bytes
        outputFile << endl;
    }


}

void dissem::endRecordAnalyzer(int row) { 
    int startAddress = stoi(objData[row].substr(1,6), NULL, 16);
    outputFile   << "\t\t\t" <<  "END" << "\t\t\t" <<symbols[startAddress] <<endl ;
    
}


void dissem::analyzeFormat2(int objCode, string opName){
    char reg = 'Z'; //z is just a placeholder for debugging
   // reg = registers.at(objCode & 0xF0);
    switch (objCode & 0xF0){        //used a switch statement because I struggle with maps in C++
        case 0:
            reg = 'A';
            break;
        case 1:
            reg = 'X';
            break;
        case 2:
            reg = 'L';
            break;
        case 3:
            reg = 'B';
            break;
        case 4:
            reg = 'S';
            break;
        case 5:
            reg = 'T';
            break;
        case 6:
            reg = 'F';
            break;    
    }
    map<char, int>::iterator it = regValue.find(reg); //idea to update map value from https://stackoverflow.com/questions/4527686/how-to-update-stdmap-after-using-the-find-method
        if (it != regValue.end())
            it->second = 0;         //clears a given register
    outputFile << "\t\t\t" << "CLEAR" << "\t\t\t" << reg << "\t\t\t\t" << objCode;
}

void dissem::analyzeFormat3(int objCode, string opName) {
    //anytime the expression (objCode & 0xFFF) is used, that is simply the disp bits from the format 3 object code
    //try-catch blocks are used to search through the map contain literals and the map containing symbols.
    //an error is thrown when the first search yields no results, leading the program to search the second map
    int flags = (objCode & 258048) >> 12;
    char reg;
    string symbol;
    if (opName=="LDA"){ //checks if value needs to be loaded into a register
        loadRegister('A', objCode, 3);
    }
    else if (opName=="LDB"){
        loadRegister('B', objCode, 3);
    }
    else if (opName=="LDF"){
        loadRegister('F', objCode, 3);
    }
    else if (opName=="LDL"){
        loadRegister('L', objCode, 3);
    }
    else if (opName=="LDS"){
        loadRegister('S', objCode, 3);
    }
    else if (opName=="LDT"){
        loadRegister('T', objCode, 3);
    }
    else if (opName=="LDX"){
        loadRegister('X', objCode, 3);
    }
    if(flags==48 || flags == 32 || flags == 16 || flags == 56){ //TA = disp or TA = disp + (X)
        if(flags==56){  //checks for indexed addressing
            //disp+X
            symbol = symbols.at((objCode & 0xFFF)+regValue.at('X')) + ",X";
        }
        else if(flags==32){//checks for indirect addressing
            try{        
                symbol = symbols.at(objCode & 0xFFF);
                
            }
            catch(...){
                for(map<int, pair<string, int>>::const_iterator itr = literals.begin();//idea for parsing 2D map from https://stackoverflow.com/questions/14070940/how-can-i-print-out-c-map-values
                    itr != literals.end(); ++itr)
                if (itr->first==(objCode & 0xFFF)){
                    symbol=itr->second.first;
                }
            }
        }
        else if(flags==16){//checks for constant
            symbol = "#"+ to_string(objCode & 0xFFF);
        }
        else{//disp      
            symbol = symbols.at(objCode & 0xFFF);
        }
    }
    else if(flags == 50 || flags == 34 || flags == 18 || flags == 58){//TA = PC + disp or TA = PC + disp + (X)
        if(flags==58){  //checks for indexed addressing
            //PC+disp+X
           symbol = symbols.at((currentAddress+3+(objCode & 0xFFF)+regValue.at('X'))&0xFFF) + ",X"; //two bitwise & operations here to get rid of carryover from addition
        }
        else if(flags==34){//checks for indirect addressing

        }
        else if(flags==18){//checks for immediate addressing
        
        }
        else{//PC+disp
            try{        
                symbol = symbols.at(((objCode & 0xFFF)+currentAddress+3)&0xFFF);
                
            }
            catch(...){
                for(map<int, pair<string, int>>::const_iterator itr = literals.begin();//idea for parsing 2D map from https://stackoverflow.com/questions/14070940/how-can-i-print-out-c-map-values
                    itr != literals.end(); ++itr)
                if (itr->first==((objCode & 0xFFF)+currentAddress+3)){
                    symbol=itr->second.first;
                }
            }
        }
    }
    else if(flags == 52 || flags == 36 || flags == 20 || flags == 60){
        if(flags==60){  //checks for indexed addressing
            //B+disp+X
            symbol = symbols.at((regValue.at('B')+(objCode & 0xFFFFF)+regValue.at('X'))&0xFFFFF) + ",X";
        }
        else if(flags==36){//checks for indirect addressing
                symbol = "@" + symbols.at((objCode & 0xFFF)+regValue.at('B'));
        }
        else{
            //B+disp
           symbol = symbols.at((objCode & 0xFFF)+regValue.at('B'));
        }
    }
    else{
        symbol = "";
    }
        outputFile << "\t\t\t" << opName << "\t\t\t" << symbol << "\t\t\t\t" << setfill('0')<< setw(6)<< objCode;
        if (opName=="LDB")
            outputFile << "\n\t\t\t" << "BASE" << "\t\t\t" << symbol.erase(0,1);
}

void dissem::analyzeFormat4(int objCode, string opName) {
    int flags = (66060288 & objCode) >> 20;
    int opCode = (4227858432 & objCode) >> 24;
    string symbol = "SMBL4";        //temporarily set to SMBL4
    if (opName=="LDA"){ //checks if value needs to be loaded into a register
        loadRegister('A', objCode, 4);
    }
    else if (opName=="LDB"){
        loadRegister('B', objCode, 4);
    }
    else if (opName=="LDF"){
        loadRegister('F', objCode, 4);
    }
    else if (opName=="LDL"){
        loadRegister('L', objCode, 4);
    }
    else if (opName=="LDS"){
        loadRegister('S', objCode, 4);
    }
    else if (opName=="LDT"){
        loadRegister('T', objCode, 4);
    }
    else if (opName=="LDX"){
        loadRegister('X', objCode, 4);
    }
    if(flags==49){  //TA = addr
        try{        //try-catch used because literals are stored in a 2D map and symbols in a 1D map
            symbol = symbols.at(objCode & 0xFFFFF);
        }
        catch(...){
            for(map<int, pair<string, int>>::const_iterator itr = literals.begin();//idea for parsing 2D map from https://stackoverflow.com/questions/14070940/how-can-i-print-out-c-map-values
                itr != literals.end(); ++itr)
            if (itr->first==(objCode & 0xFFFFF)){
                symbol=itr->second.first;
            }
        }
    }
    else if(flags==33){//checks for indirect addressing
        try{        //try-catch used because literals are stored in a 2D map and symbols in a 1D map
            symbol = "@" + symbols.at((objCode & 0xFFFFF)); 
        }
        catch(...){
            for(map<int, pair<string, int>>::const_iterator itr = literals.begin();//idea for parsing 2D map from https://stackoverflow.com/questions/14070940/how-can-i-print-out-c-map-values
                itr != literals.end(); ++itr)
            if (itr->first==(objCode & 0xFFFFF)){
                symbol= "@" + itr->second.first;
            }
        }      
    }
    else if(flags==17){//checks for constant
        symbol = "#"+ symbols.at(objCode & 0xFFFFF);
    }
    else{//indexed addressing
        //TA = addr + X
        symbol = symbols.at((currentAddress+4+(objCode & 0xFFFFF)+regValue.at('X'))&0xFFFFF) + ",X"; //2nd bitwise is to account for carryover in addition when calculating TA
    }
        outputFile << "\t+"+ opName << "\t\t\t" << symbol << "\t\t\t\t" << setfill('0')<< setw(8)<< objCode;
        if (opName=="LDB")
            outputFile << "\n\t\t\t" << "BASE" << "\t\t\t" << symbol.erase(0,1);
}
void dissem::loadRegister(char reg, int objCode, int format){
    if (format==3){         //solution for updating registers is inspired by this posting https://stackoverflow.com/questions/4527686/how-to-update-stdmap-after-using-the-find-method
        std::map<char, int>::iterator it = regValue.find(reg); 
            it->second=(objCode & 0xFFF);
    }
    else{//for format 4
        std::map<char, int>::iterator it = regValue.find(reg); 
            it->second=(objCode & 0xFFFFF);
    }
}