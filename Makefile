# Don't print the commands unless explicitely requested with `make V=1`
ifneq ($(V),1)
Q = @
V = 0
endif

# Compiler
CXX := g++
CXX_FLAGS := -Wall -Werror -std=c++11

# Include path
SERIAL_CPP := ./serial/%.cpp
PARALLEL_CPP := ./parallel/bitonicSort_parallel.cpp \
 			  	./parallel/mergeSort_parallel.cpp \
			  	./parallel/quickSort_parallel.cpp
TEST_DIR := ./test
OBJ_DIR = ./objs

# Current directory
CUR_PWD := $(shell pwd)

all: $(patsubst ./serial/%.cpp, ./bin/%.out, $(wildcard ./serial/*.cpp)) $(patsubst ./test/%.cpp, ./bin/%.out, $(wildcard ./test/*.cpp))

# Rule for programs
./bin/%.out: ./serial/%.cpp Makefile
	@echo "MAKE     $@"
	$(Q)$(CXX) $(CXX_FLAGS) -o $@ $<

./bin/%.out: ./test/%.cpp Makefile
	@echo "MAKE     $@"
	$(Q)$(CXX) $(CXX_FLAGS) -o $@ $<

# Cleaning rule
clean:
	@echo "CLEAN    $(CUR_PWD)"
	$(Q)rm -f bin/*

.PHONY: clean bin/*