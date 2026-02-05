# Makefile containing macros
# for Lab05, CS 16, W26
# by Z. Matni
#
CXX=clang++

CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

BINARIES=lab05Test vectorSplit converter

all: ${BINARIES}

vectorSplit: vectorSplit.cpp 
	${CXX} $^ -o $@

converter: converter.cpp 
	${CXX} $^ -o $@

lab05Test: lab05Test.cpp 
	${CXX} $^ -o $@

clean: 
	rm -f ${BINARIES} *.o
