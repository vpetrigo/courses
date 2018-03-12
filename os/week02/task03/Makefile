CC := clang
CXX := clang++
CXXFLAGS := -std=c++11 -Wall
SRC := cache_alloc.cpp
OBJ := $(patsubst %.cpp,%.o,$(SRC))

.PHONY: valgrind clean

all: $(OBJ)
	$(CXX) -o cache_alloc $?

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

valgrind:
	@valgrind --tool=memcheck --leak-check=full ./cache_alloc

clean:
	@rm -rf $(OBJ) cache_alloc