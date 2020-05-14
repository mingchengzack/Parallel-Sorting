# Don't print the commands unless explicitely requested with `make V=1`
ifneq ($(V),1)
Q = @
V = 0
endif

# Compiler
CXX := g++
CXX_FLAGS := -Wall -Werror -std=c++11
THREAD_FLAG := -pthread

# Current directory
CUR_PWD := $(shell pwd)

# Include path
SORTING_PATH := ./serial
TEST_DIR := ./test
OBJ_DIR = ./objs
INCLUDE := -I $(SORTING_PATH)

# Main program
program := bin/main.out
objs := $(OBJ_DIR)/main.o
SORTING_HPP := $(SORTING_PATH)/mergeSort.hpp \
			   $(SORTING_PATH)/bitonicSort.hpp \
			   $(SORTING_PATH)/quickSort.hpp

all: $(program)

# Rule for main program
$(program): $(objs)
	@echo "MAKE     $@"
	$(Q)$(CXX) $(CXX_FLAGS) -o $@ $<

# Generic rule for compiling objects
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(SORTING_HPP)
	@echo "CXX       $@"
	$(Q)$(CXX) $(CXX_FLAGS) $(INCLUDE) -c -o $@ $<

# Cleaning rule
clean:
	@echo "CLEAN    $(CUR_PWD)"
	$(Q)rm -f $(program) $(objs)

.PHONY: clean $(program)