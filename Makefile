#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#*******************************************************************

CC = g++ -Wall -Werror
IDIR = /usr/local/include
CFLAGS = -I $(IDIR)
TESTS = matrix_test math_test tree_test difq_test
MATH_HDR = ${wildcard math/*.h}
MATH_OBJ = ${wildcard math/*.o}
DIST_HDR = ${wildcard distribution/*.h}
TREE_HDR = ${wildcard tree/*.h}
PHYS_HDR = ${wildcard physics/.h}

all: $(TESTS)
	@echo "Build successful"
	@date
	
math/ode.o: math/ode.cc
	@echo "Creating obj file ode.o..."
	@$(CC) -c math/ode.cc -o math/ode.o
	
difq_test: difq_test.cc $(MATH_OBJ)
	@echo "Building difq_test..."
	@$(CC) -o difq_test difq_test.cc $(MATH_OBJ) $(CFLAGS)
	
matrix_test: matrix_test.cc $(MATH_HDR)
	@echo "Building matrix_test..."
	@$(CC) -o matrix_test matrix_test.cc $(CFLAGS)
	
math_test: math_test.cc $(MATH_HDR) $(DIST_HDR)
	@echo "Building math_test..."
	@$(CC) -o math_test math_test.cc $(CFLAGS)

tree_test: tree_test.cc $(TREE_HDR)
	@echo "Building tree_test..."
	@$(CC) -o tree_test tree_test.cc $(CFLAGS)
	
clean:
	@echo "****Removing test routines****"
	@for test in $(TESTS) ; do \
		rm $$test ; \
		echo "   deleted" $$test ; \
	done
	@echo "****Test routines removed****"

