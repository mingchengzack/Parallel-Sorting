# Don't print the commands unless explicitely requested with `make V=1`
ifneq ($(V),1)
Q = @
V = 0
endif

# Compiler
CXX := g++
CXX_FLAGS := -Wall -Werror -std=c++11
CXX_OPENMP := icpc -qopenmp

# Current directory
CUR_PWD := $(shell pwd)

all: $(patsubst ./serial/%.cpp, ./bin/%.out, $(wildcard ./serial/*.cpp)) \
	$(patsubst ./test/%.cpp, ./bin/%.out, $(wildcard ./test/*.cpp)) \
	$(patsubst ./parallel/%.cpp, ./bin/%.out, $(wildcard ./parallel/*.cpp))

# Rule for programs
./bin/%.out: ./parallel/%.cpp
	@echo "MAKE     $@"
	$(Q)$(CXX_OPENMP) $(CXX_FLAGS) -o $@ $<

./bin/%.out: ./serial/%.cpp
	@echo "MAKE     $@"
	$(Q)$(CXX_OPENMP) $(CXX_FLAGS) -o $@ $<

./bin/%.out: ./test/%.cpp
	@echo "MAKE     $@"
	$(Q)$(CXX) $(CXX_FLAGS) -o $@ $<

# Cleaning rule
clean:
	@echo "CLEAN    $(CUR_PWD)"
	$(Q)rm -f bin/*

.PHONY: clean bin/*
