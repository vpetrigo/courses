CXXFLAGS = -std=c++14 -O3
SRC = paging.cpp
CXX = clang++
OBJ = $(SRC:%.cpp=%.o)

.PHONY: all clean

all: paging

paging: $(SRC)
	$(CXX) -o $@ $< $(CXXFLAGS)

clean:
	rm -f paging
