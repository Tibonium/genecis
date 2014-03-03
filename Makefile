#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#*******************************************************************

CC = g++ -Wall -Werror
IDIR = /usr/local/include
CFLAGS = -I $(IDIR)
TESTS = matrix_test math_test tree_test
#OBJ_DIR = tree math distribution
#OBJ_SRCS = tree/trees.h math/mathematics.h distribution/distribution.h
#OBJECTS := $(SRCS:.h=.o)
#FILTER := physics_test.cc
#TESTS1 := $(filter-out $(FILTER),$(wildcard *.cc))

#DEPENDENCIES := $(OBJECTS)

##objects: $(OBJECTS)
##	$(CC) -c $@ -o $<

#.PHONY: archive

#archive: GENeCIS.a

#GENeCIS.a: $(OBJECTS)
#	@echo "Scanning dependencies..."
#	$(AR) $@ $^
#	
#-include $(DEPENDENCIES)

#$(OBJECTS): $(SRCS)
#	$(CC) $(CFLAGS) -c $< -o $@

all: $(TESTS)
	@echo "Build successful"

tree/trees.o: $(wildcard tree/*.h)
	@echo "Building tree.o..."
	@$(CC) -c tree/trees.h -o tree/trees.o
	
distribution/distribution.o: $(wildcard distribution/*.h)
	@echo "Building distribution.o..."
	@$(CC) -c distribution/distribution.h -o distribution/distribution.o
	
math/mathematics.o: $(wildcard math/*.h)
	@echo "Building mathematics.o..."
	@$(CC) -c math/mathematics.h -o math/mathematics.o
	
matrix_test: matrix_test.cc math/mathematics.o
	@echo "Building matrix_test..."
	@$(CC) -o matrix_test matrix_test.cc $(CFLAGS)
	
math_test: math_test.cc math/mathematics.o distribution/distribution.o
	@echo "Building math_test..."
	@$(CC) -o math_test math_test.cc $(CFLAGS)

tree_test: tree_test.cc tree/trees.o
	@echo "Building tree_test..."
	@$(CC) -o tree_test tree_test.cc $(CFLAGS)
	
clean:
	@echo "****Removing test routines****"
	@for test in $(TESTS) ; do \
		rm $$test ; \
		echo "   deleted" $$test ; \
	done
	@echo "****Test routines removed****"

