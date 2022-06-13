CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

.PHONY: tests clean

exec: bin/exec

bin/exec: ./src/main.cc ./includes/binary_search_tree.hpp ./includes/binary_search_tree_more.hpp ./includes/node.hpp 
	$(CXX) $(CXXFLAGS) ./src/main.cc -o $@

main.o: src/main.cc includes/binary_search_tree.hpp includes/node.hpp includes/binary_search_tree_more.hpp
	${CXX} ${CXX_FLAGS} -c src/main.cc 

tests: tests.o restaurant.o
	${CXX} ${CXX_FLAGS} -lc++abi bin/tests.o bin/restaurant.o -o bin/tests

tests.o: tests/catch.hpp tests/tests.cc restaurant.o includes/supplier.hpp includes/customer.hpp
	${CXX} ${CXX_FLAGS} -c tests/tests.cc -o bin/tests.o

restaurant.o: includes/restaurant.hpp src/restaurant.cc includes/supplier.hpp includes/customer.hpp
	${CXX} ${CXX_FLAGS} -c src/restaurant.cc -o bin/restaurant.o

clean:
	-rm -f *.o bin/main bin/tests bin/exec bin/main.o bin/restaurant.o bin/tests.o
