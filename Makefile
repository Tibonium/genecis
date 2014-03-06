#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#*******************************************************************

CC = g++ -Wall -Werror
IDIR = /usr/local/include
CFLAGS = -I $(IDIR)
TESTS = matrix_test math_test tree_test
MATH_PCKG = ${wildcard math/*.h}
DIST_PCKG = ${wildcard distribution/*.h}
TREE_PCKG = ${wildcard tree/*.h}
PHYS_PCKG = ${wildcard physics/.h}

all: $(TESTS)
	@echo "Build successful"
	
matrix_test: matrix_test.cc $(MATH_PCKG)
	@echo "Building matrix_test..."
	@$(CC) -o matrix_test matrix_test.cc $(CFLAGS)
	
math_test: math_test.cc $(MATH_PCKG) $(DIST_PCKG)
	@echo "Building math_test..."
	@$(CC) -o math_test math_test.cc $(CFLAGS)

tree_test: tree_test.cc $(TREE_PCKG)
	@echo "Building tree_test..."
	@$(CC) -o tree_test tree_test.cc $(CFLAGS)
	
clean:
	@echo "****Removing test routines****"
	@for test in $(TESTS) ; do \
		rm $$test ; \
		echo "   deleted" $$test ; \
	done
	@echo "****Test routines removed****"

