CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/

.PHONY: tests clean

exec: driver.o obj/bank.o
	mkdir -p bin
	${CXX} ${CXX_FLAGS} -lc++abi obj/driver.o obj/bank.o -o bin/exec

driver.o: src/driver.cc bank.o includes/account.hpp
	mkdir -p obj
	${CXX} ${CXX_FLAGS} -c src/driver.cc -o obj/driver.o

tests: test.o bank.o
	mkdir -p bin
	${CXX} ${CXX_FLAGS} -lc++abi obj/test.o obj/bank.o -o bin/tests

test.o: tests/catch.hpp tests/test.cc includes/bank.hpp includes/account.hpp
	mkdir -p obj
	${CXX} ${CXX_FLAGS} -c tests/test.cc -o obj/test.o

bank.o: includes/bank.hpp src/bank.cc includes/account.hpp
	mkdir -p obj
	${CXX} ${CXX_FLAGS} -c src/bank.cc -o obj/bank.o

clean:
	rm -f bin/* obj/*
