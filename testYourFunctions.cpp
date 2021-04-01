#include <iostream>
#include <map>
using namespace std;
map<int,string> symbols; //Address and the associated Symbol 
map<int, string> literalZ; //Address and the associated literal
map<int, char> registers;
int main(int argc, char **argv) {
    symbols.insert(pair<int,string>(1, "hello1"));
    symbols.insert(pair<int,string>(7, "hello7"));
    symbols.insert(pair<int,string>(13, "hello13"));
    literalZ.insert(pair<int,string>(6,"hello6"));
    literalZ.insert(pair<int,string>(5,"hello5"));
    literalZ.insert(pair<int,string>(9,"hello9"));
    registers.insert(pair<int,char>(4,'h'));
    registers.insert(pair<int,char>(0,'p'));
    registers.insert(pair<int,char>(10,'c'));
    int num = 0;
    char character;
    string val;
    map<int,string>::iterator it ;  
    map<int,char>::iterator it1 ;
    it = symbols.find(num);
    try{
        val = it->second;
        cout<<"val is: " << val << endl;
    }
    catch(...){}
    if(it==symbols.end()){
        it = literalZ.find(num);
        try{
            val = it->second;
            cout<<"val is: " << val << endl;
        }
        catch(...){}
        if(it==literalZ.end()){
            it1=registers.find(num);
            character = it1->second;
            cout<<"character is: " << character << endl;
        }
    } 
}