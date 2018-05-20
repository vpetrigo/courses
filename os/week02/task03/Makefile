CC := gcc
CXX := g++
CXXFLAGS := -std=c++11 -Wall -DLOCAL_PC
LDFLAGS :=
SRC := cache_alloc.cpp
OBJ := $(patsubst %.cpp,%.o,$(SRC))

.PHONY: valgrind clean

all: $(OBJ)
	$(CXX) -o cache_alloc $? $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

valgrind:
	@valgrind --tool=memcheck --leak-check=full ./cache_alloc

clean:
	@rm -rf $(OBJ) *.out cache_alloc
