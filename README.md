**Name:** Jamshid Aziz
**Partner:** Chance Daily


The following are the functions from _dissem.cpp_ file

--> `dissem::dissem(string objFileName, string symFileName)`
  * The consttructor recieves 2 file names
  * The object file name, and the symbol file name
  * Opens the files & stores the data in objData, symbols, literals respectively
  * Traverses through each record in the object file & calls either 
  * Head/Text/End record analyzer functions, which recieve the row index
  * Closes files when done

--> `void dissem::textRecordAnalyzer(int row)`
  * This function traverses through each object code & calls the 
  * Function accoridng to it's format 2/3/4
  * It's responsible for writing to output file the following:
  * Current Address, the symbol names, reserving buffer, 
  * And defining the literals 


--> `void dissem::analyzeFormat2(int objCode, string opName)`
  * This function analyzes format 2 instructions and
  * Writes the following to the output file:
  * Op Code name, Target Address, and the Obejct code 

--> `void dissem::analyzeFormat3(int objCode, string opName)`

--> `void dissem::analyzeFormat4(int objCode, string opName)`




The following are the functions from _OpCodes.cpp_ file.
  * This class was used as a lookup table for the Directive names,
  * Given an opcode, and figuring out the format

--> `string getSymbolName(int threeHalfBytes)`
  * This fucntion recieves a hex value in the form 0x111
  * Filters out the first six bits and then finds the 
  * Opcode matching those six bits 
  * returns the Symbol associated with the first six bits 

--> `int getFormat(int threeHalfBytes)`
  * This function recieves a hex value in the form 0x111
  * First checks if it's format 2
  * Then checks if it's format 3 or 4
  * Finally returns the format number as an integer value

