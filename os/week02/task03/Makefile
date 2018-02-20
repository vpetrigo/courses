CC := clang
CXX := clang++
CFLAGS := -std=c++11 -Wall
SRC := cache_alloc.cpp
OBJ := $(patsubst %.cpp,%.o,$(SRC))

all: $(OBJ)
	$(CXX) -o cache_alloc $?

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)