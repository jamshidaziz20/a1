# Developed by 
# Name: Jamshid Aziz   ID:  821340982 
# Name Chance Daily    ID:  821689902

# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -g

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
dissem : dissem.o OpCodes.o 
	$(CXX) $(CXXFLAGS) -o dissem $^

dissem.o : dissem.cpp dissem.h
	$(CXX) $(CXXFLAGS) -c dissem.cpp


OpCodes.o : OpCodes.cpp OpCodes.h
	$(CXX) $(CXXFLAGS) -c OpCodes.cpp


clean :
	rm *.o

