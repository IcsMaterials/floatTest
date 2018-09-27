CXX := g++
CXX_FLAGS := -g -std=c++14


all: test main

main: engine.o common.o start.o main.cpp float.hpp
	${CXX}  $^ ${CXX_FLAGS} -o $@ #-DEXP=4 -DFRAC=3

test: engine.o common.o test.cpp float.hpp
	g++ $^ -o $@ -g -std=c++14

#start.o: common.o engine.o start.h start.cpp
#	${CXX} -c $^ ${CXX_FLAGS}

%.o: %.h %.cpp
	${CXX} -c $^ ${CXX_FLAGS}
