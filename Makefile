#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#		 The user needs to have the environment variables
#		 GENECIS_BUILD and GENECIS_SRC set to the the source and
#		 build directories, respectively, on their system.
#
#*******************************************************************

CC = g++ -g -O0 -Wall -std=c++98
IDIR = /usr/local/include
INSTALL_PATH = $(IDIR)/genecis
BUILD_PATH = $(shell echo $(GENECIS_BUILD))
SRC_PATH = $(shell echo $(GENECIS_SRC))
GENECIS_FOLDERS = ai algorithm base container distribution tree \
	physics net math
CFLAGS = -I $(IDIR)
TESTS = matrix_test distribution_test tree_test difq_test server_test \
	socket_test graph_test prime sort_test vector_test mathfunc_test \
	container_test graph_array_test pattern_test#	gravity_test
MISC_TESTS = hash_test reference_test boost_test buffer_test template_test
MATRIX = $(SRC_PATH)/math/matrix.h $(SRC_PATH)/math/matrix_expression.h \
	$(SRC_PATH)/math/matrix_operations.h $(SRC_PATH)/math/matrix_io.h
VECTOR = $(SRC_PATH)/math/bvector.h $(SRC_PATH)/math/svector.h \
	$(SRC_PATH)/math/cvector.h $(SRC_PATH)/math/vector_expression.h
CONTAINER = $(SRC_PATH)/container/array.h $(SRC_PATH)/container/dynamic_array.h \
	$(SRC_PATH)/container/container_io.h $(SRC_PATH)/container/container_expression.h \
	$(SRC_PATH)/base/genecis_functions.h
MATH_HDR = ${wildcard $(SRC_PATH)/math/*.h}
AI_HDR = ${wildcard $(SRC_PATH)/ai/*.h}
ALGO_HDR = ${wildcard $(SRC_PATH)/algorithm/*.h}
BASE_HDR = ${wildcard $(SRC_PATH)/base/*.h}
CONT_HDR = ${wildcard $(SRC_PATH)/container/*.h}
DIST_HDR = ${wildcard $(SRC_PATH)/distribution/*.h}
TREE_HDR = ${wildcard $(SRC_PATH)/tree/*.h}
PHYS_HDR = ${wildcard $(SRC_PATH)/physics/*.h}
SRVR_HDR = ${wildcard $(SRC_PATH)/net/*.h}
SRVR_FILES = ${wildcard $(SRC_PATH)/net/*.cc}

MATH_OBJ = ${wildcard $(SRC_PATH)/math/*.o}
AI_OBJ = ${wildcard $(SRC_PATH)/ai/*.o}
PHYS_OBJ = ${wildcard $(SRC_PATH)/physics/*.o}
SRVR_OBJ = $(wildcard $(SRC_PATH)/net/*.o)

all: regression_test misc_test
	@date
	
install:
	@for main in $(INSTALL_PATH) ; do \
		if [ ! -d "$(INSTALL_PATH)" ] ; \
		then \
			mkdir -p $$main ; \
		fi ; \
	done
	@for folder in $(GENECIS_FOLDERS) ; do \
		if [ ! -d "$(INSTALL_PATH)/$$folder" ] ; \
		then \
			mkdir -p $(INSTALL_PATH)/$$folder ; \
		fi ; \
	done
	@for file in $(AI_HDR) ; do \
		cp $$file $(INSTALL_PATH)/ai/ ; \
	done
	@for file in $(ALGO_HDR) ; do \
		cp $$file $(INSTALL_PATH)/algorithm/ ; \
	done
	@for file in $(BASE_HDR) ; do \
		cp $$file $(INSTALL_PATH)/base/ ; \
	done
	@for file in $(CONT_HDR) ; do \
		cp $$file $(INSTALL_PATH)/container/ ; \
	done
	@for file in $(DIST_HDR) ; do \
		cp $$file $(INSTALL_PATH)/distribution/ ; \
	done
	@for file in $(TREE_HDR) ; do \
		cp $$file $(INSTALL_PATH)/tree/ ; \
	done
	@for file in $(MATH_HDR) ; do \
		cp $$file $(INSTALL_PATH)/math/ ; \
	done
	@for file in $(PHYS_HDR) ; do \
		cp $$file $(INSTALL_PATH)/physics/ ; \
	done
	@for file in $(SRVR_HDR) ; do \
		cp $$file $(INSTALL_PATH)/net/ ; \
	done
	
clean:
	@echo "The following tests have been removed: "
	@for test in $(TESTS) ; do \
		if [ -a $$test ] ; \
		then \
			rm $(BUILD_PATH)/$$test ; \
			echo "  " $$test ; \
		fi ; \
	done
	@for test in $(MISC_TESTS) ; do \
		if [ -a $$test ] ; \
		then \
			rm $(BUILD_PATH)/$$test ; \
			echo "  " $$test ; \
		fi ; \
	done

# Various miscellaneous test
misc_test: $(MISC_TESTS)
	@echo "Miscellaneous Tests built"

reference_test: $(SRC_PATH)/misc_test/reference_test.cc
	@echo "Building reference_test..."
	@$(CC) -o $(BUILD_PATH)/reference_test $(SRC_PATH)/misc_test/reference_test.cc $(CFLAGS)
	
boost_test: $(SRC_PATH)/misc_test/boost_test.cc
	@echo "Building boost_test..."
	@$(CC) -o $(BUILD_PATH)/boost_test $(SRC_PATH)/misc_test/boost_test.cc $(CFLAGS)
	
hash_test: $(SRC_PATH)/misc_test/hash_test.cc
	@echo "Building hash_test..."
	@$(CC) -o $(BUILD_PATH)/hash_test $(SRC_PATH)/misc_test/hash_test.cc $(CFLAGS)

buffer_test: $(SRC_PATH)/misc_test/buffer_test.cc
	@echo "Building buffer_test..."
	@$(CC) -o $(BUILD_PATH)/buffer_test $(SRC_PATH)/misc_test/buffer_test.cc $(CFLAGS)

template_test: $(SRC_PATH)/misc_test/template_test.cc
	@echo "Building template_test..."
	@$(CC) -o $(BUILD_PATH)/template_test $(SRC_PATH)/misc_test/template_test.cc $(CFLAGS)

# Regression Tests
regression_test: $(TESTS)
	@echo "Regression Tests built"

math/ode.o: $(SRC_PATH)/math/ode.cc $(SRC_PATH)/math/ode.h
	@echo "Creating obj file ode.o..."
	@$(CC) -c $(SRC_PATH)/math/ode.cc -o $(SRC_PATH)/math/ode.o
	
difq_test: $(SRC_PATH)/test/difq_test.cc $(SRC_PATH)/math/ode.o
	@echo "Building difq_test..."
	@$(CC) -o $(BUILD_PATH)/difq_test $(SRC_PATH)/test/difq_test.cc $(SRC_PATH)/math/ode.o $(CFLAGS)
		
matrix_test: $(SRC_PATH)/test/matrix_test.cc $(MATRIX)
	@echo "Building matrix_test..."
	@$(CC) -o $(BUILD_PATH)/matrix_test $(SRC_PATH)/test/matrix_test.cc $(CFLAGS)
	
distribution_test: $(SRC_PATH)/test/distribution_test.cc
	@echo "Building distribution_test..."
	@$(CC) -o $(BUILD_PATH)/distribution_test $(SRC_PATH)/test/distribution_test.cc $(CFLAGS)

tree_test: $(SRC_PATH)/test/tree_test.cc
	@echo "Building tree_test..."
	@$(CC) -o $(BUILD_PATH)/tree_test $(SRC_PATH)/test/tree_test.cc $(CFLAGS)
	
graph_test: $(SRC_PATH)/test/graph_test.cc
	@echo "Building graph_test..."
	@$(CC) -o $(BUILD_PATH)/graph_test $(SRC_PATH)/test/graph_test.cc $(CFLAGS)
	
vector_test: $(SRC_PATH)/test/vector_test.cc $(VECTOR)
	@echo "Building vector_test..."
	@$(CC) -o $(BUILD_PATH)/vector_test $(SRC_PATH)/test/vector_test.cc $(CFLAGS)

container_test: $(SRC_PATH)/test/container_test.cc $(CONTAINER)
	@echo "Building container_test..."
	@$(CC) -o $(BUILD_PATH)/container_test $(SRC_PATH)/test/container_test.cc $(CFLAGS)

prime: $(SRC_PATH)/test/prime.cc
	@echo "Building prime_test..."
	@$(CC) -o $(BUILD_PATH)/prime $(SRC_PATH)/test/prime.cc $(CFLAGS)
	
sort_test: $(SRC_PATH)/test/sort_test.cc
	@echo "Building sort_test..."
	@$(CC) -o $(BUILD_PATH)/sort_test $(SRC_PATH)/test/sort_test.cc $(CFLAGS)
	
mathfunc_test:  $(SRC_PATH)/test/mathfunc_test.cc
	@echo "Building mathfunc_test..."
	@$(CC) -o $(BUILD_PATH)/mathfunc_test $(SRC_PATH)/test/mathfunc_test.cc $(CFLAGS)
	
math/graph_array.o: $(SRC_PATH)/math/graph_array.cc math/graph_array.h
	@echo "Creating obj file graph_array.o..."
	@$(CC) -c $(SRC_PATH)/math/graph_array.cc -o $(SRC_PATH)/math/graph_array.o
	
graph_array_test: $(SRC_PATH)/test/graph_array_test.cc $(SRC_PATH)/math/graph_array.o
	@echo "Building graph_array_test..."
	@$(CC) -o $(BUILD_PATH)/graph_array_test $(SRC_PATH)/test/graph_array_test.cc \
		$(SRC_PATH)/math/graph_array.o $(CFLAGS)

ai/number_pattern.o: $(SRC_PATH)/ai/number_pattern.cc $(SRC_PATH)/ai/number_pattern.h
	@echo "Creating obj file number_pattern.o..."
	@$(CC) -c $(SRC_PATH)/ai/number_pattern.cc -o $(SRC_PATH)/ai/number_pattern.o

pattern_test: $(SRC_PATH)/test/pattern_test.cc $(SRC_PATH)/ai/number_pattern.o
	@echo "Building pattern_test..."
	@$(CC) -o $(BUILD_PATH)/pattern_test $(SRC_PATH)/test/pattern_test.cc \
		$(SRC_PATH)/ai/number_pattern.o $(CFLAGS)
	
# Server Tests
server: socket_test server_test
	@echo "Server build complete"
	@date

net/isocket.o: $(SRC_PATH)/net/isocket.cc $(SRC_PATH)/net/isocket.h
	@echo "Creating server obj file net/isocket.o..."
	@$(CC) -c $(SRC_PATH)/net/isocket.cc -o $(SRC_PATH)/net/isocket.o

net/genecis_server.o: $(SRC_PATH)/net/genecis_server.cc
	@echo "Creating server obj file net/genecis_server.o..."
	@$(CC) -c $(SRC_PATH)/net/genecis_server.cc -o $(SRC_PATH)/net/genecis_server.o

socket_test: $(SRC_PATH)/test/socket_test.cc $(SRVR_OBJ)
	@echo "Building socket_test..."
	@$(CC) -o $(BUILD_PATH)/socket_test $(SRC_PATH)/test/socket_test.cc $(SRC_PATH)/net/isocket.o $(CFLAGS)

server_test: $(SRC_PATH)/test/server_test.cc $(SRVR_OBJ)
	@echo "Building server_test..."
	@$(CC) -o $(BUILD_PATH)/server_test $(SRC_PATH)/test/server_test.cc $(SRVR_OBJ) $(CFLAGS)
	
# Physics Tests
gravity_test: $(SRC_PATH)/test/gravity_test.cc $(SRC_PATH)/physics/gravity.o physics/gravity.h
	@echo "Building gravity_test..."
	@$(CC) -o $(BUILD_PATH)/gravity_test $(SRC_PATH)/test/gravity_test.cc $(SRC_PATH)/physics/gravity.o $(CFLAGS)
		
physics/gravity.o: $(SRC_PATH)/physics/gravity.cc
	@echo "Creating obj file gravity.o..."
	@$(CC) -c $(SRC_PATH)/physics/gravity.cc -o $(SRC_PATH)/physics/gravity.o
	
#physics/gravity_netcdf.o: $(SRC_PATH)/physics/gravity_netcdf.cc
#	@echo "Creating obj file gravity_netcdf.o..."
#	@$(CC) -c $(SRC_PATH)/physics/gravity_netcdf.cc -o -lnetcdf $(SRC_PATH)/physics/gravity_netcdf.o

