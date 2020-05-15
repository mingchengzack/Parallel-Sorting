# Don't print the commands unless explicitely requested with `make V=1`
ifneq ($(V),1)
Q = @
V = 0
endif

# Compiler
CXX := g++
CXX_FLAGS := -Wall -Werror -std=c++11

# Include path
SERIAL_CPP := ./serial/bitonicSort_serial.cpp \
 			  ./serial/mergeSort_serial.cpp \
			  ./serial/quickSort_serial.cpp
PARALLEL_CPP := ./parallel/bitonicSort_parallel.cpp \
 			  	./parallel/mergeSort_parallel.cpp \
			  	./parallel/quickSort_parallel.cpp
TEST_DIR := ./test
OBJ_DIR = ./objs

# Main program
program := bin/bitonicSort_serial.out \
		   bin/mergeSort_serial.out \
		   bin/quickSort_serial.out

all: $(program)

# Rule for programs
$(program): $(SERIAL_CPP)
	@echo "MAKE     $@"
	$(Q)$(CXX) $(CXX_FLAGS) -o $@ $<

# Cleaning rule
clean:
	@echo "CLEAN    $(CUR_PWD)"
	$(Q)rm -f $(program) $(objs)

.PHONY: clean $(program)