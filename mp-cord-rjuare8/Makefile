CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

.PHONY: clean

exec: bin/exec

bin/exec: ./src/driver.cc ./includes/cord-utilities.hpp ./includes/cord.hpp ./includes/cs128referencelist.hpp
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/cord-utilities.cc ./src/cord.cc -o $@



clean:
	-rm -f *.o bin/main bin/tests bin/exec