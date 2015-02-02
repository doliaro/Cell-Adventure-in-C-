CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -g
CXXFLAGS += -pedantic-errors


SRCS =  main.cpp adventure.cpp

HEADERS = adventure.hpp

adventure: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o adventure
