CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

.PHONY: clean

exec: bin/exec

bin/exec: ./src/driver.cc ./includes/illini_book.hpp ./includes/utilities.hpp  
	$(CXX) $(CXXFLAGS) ./src/driver.cc src/illini_book.cc src/utilities.cc -o $@



clean:
	-rm -f *.o bin/main bin/tests bin/exec bin/main.o bin/restaurant.o bin/tests.o