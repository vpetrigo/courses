CXXFLAGS = -std=c++14 -O3
SRC = paging.cpp
CXX = g++
OBJ = $(SRC:%.cpp=%.o)

all: paging

paging: $(SRC)
	$(CXX) -o $@ $< $(CXXFLAGS)
