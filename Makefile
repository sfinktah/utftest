##########################################################################
# unit tests
##########################################################################

# additional flags
# -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wno-ctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wno-float-equal

CXXFLAGS += -std=c++1z 
CPPFLAGS += -I.

##############################################################################
# main rules
##############################################################################

all: testutf2

testutf2: testutf2.cpp
	g++ -I. -std=c++1z testutf2.cpp -o testutf2 && ./testutf2
