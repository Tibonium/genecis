#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#*******************************************************************

CC = g++ -Wall -Werror
IDIR = /usr/local/include
CFLAGS = -I $(IDIR)
TESTS = matrix_test math_test tree_test

all: matrix_test math_test tree_test

matrix_test: matrix_test.cc
	@$(CC) -o matrix_test matrix_test.cc $(CFLAGS)
	@echo "matrix_test ** built successfully **"
	
math_test: math_test.cc
	@$(CC) -o math_test math_test.cc $(CFLAGS)
	@echo "math_test   ** built successfully **"

tree_test: tree_test.cc
	@$(CC) -o tree_test tree_test.cc $(CFLAGS)
	@echo "tree_test   ** built successfully **"
	
clean:
	@echo "****Removing test routines****"
	@for test in $(TESTS) ; do \
		rm $$test ; \
		echo "   deleted" $$test ; \
	done
	@echo "****Test routines removed****"

