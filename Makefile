#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#*******************************************************************

CC = g++ -Wall -Werror -std=c++98
IDIR = /usr/local/include
CFLAGS = -I $(IDIR)
TESTS = matrix_test math_test tree_test difq_test server_test \
	socket_test graph_test prime sort_test
MATH_HDR = ${wildcard math/*.h}
MATH_OBJ = ${wildcard math/*.o}
DIST_HDR = ${wildcard distribution/*.h}
TREE_HDR = ${wildcard tree/*.h}
PHYS_HDR = ${wildcard physics/*.h}

SRVR_FILES = ${wildcard net/*.cc}
SRVR_OBJ = $(SRVR_FILES:.cc=.o)

all: $(TESTS)
	@echo "Build successful"
	@date
	
math/ode.o: math/ode.cc
	@echo "Creating obj file ode.o..."
	@$(CC) -c math/ode.cc -o math/ode.o
	
difq_test: test/difq_test.cc $(MATH_OBJ)
	@echo "Building difq_test..."
	@$(CC) -o difq_test test/difq_test.cc $(MATH_OBJ) $(CFLAGS)
	
matrix_test: test/matrix_test.cc $(MATH_HDR)
	@echo "Building matrix_test..."
	@$(CC) -o matrix_test test/matrix_test.cc $(CFLAGS)
	
math_test: test/math_test.cc $(MATH_HDR) $(DIST_HDR)
	@echo "Building math_test..."
	@$(CC) -o math_test test/math_test.cc $(CFLAGS)

tree_test: test/tree_test.cc $(TREE_HDR)
	@echo "Building tree_test..."
	@$(CC) -o tree_test test/tree_test.cc $(CFLAGS)
	
graph_test: test/graph_test.cc tree/graph_tree.h
	@echo "Buidling graph_test..."
	@$(CC) -o graph_test test/graph_test.cc $(CFLAGS)
	
clean:
	@echo "****Removing test routines****"
	@for test in $(TESTS) ; do \
		rm $$test ; \
		echo "   deleted" $$test ; \
	done
	@echo "****Test routines removed****"

server: socket_test server_test
	@echo "Server build complete"
	@date

net/isocket.o: net/isocket.cc
	@echo "Creating server obj file net/isocket.o..."
	@$(CC) -c net/isocket.cc -o net/isocket.o

net/genecis_server.o: net/genecis_server.cc
	@echo "Creating server obj file net/genecis_server.o..."
	@$(CC) -c net/genecis_server.cc -o net/genecis_server.o

socket_test: test/socket_test.cc $(SRVR_OBJ)
	@echo "Building socket_test..."
	@$(CC) -o socket_test test/socket_test.cc net/isocket.o $(CFLAGS)

server_test: test/server_test.cc $(SRVR_OBJ)
	@echo "Building server_test..."
	@$(CC) -o server_test test/server_test.cc $(SRVR_OBJ) $(CFLAGS)
	
prime: math/prime.cc
	@echo "Building prime_test..."
	@$(CC) -o prime math/prime.cc $(CFLAGS)
	
sort_test: test/sort_test.cc
	@echo "Building sort_test..."
	@$(CC) -o sort_test test/sort_test.cc $(CFLAGS)
