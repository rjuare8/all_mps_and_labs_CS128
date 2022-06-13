CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cc includes/clickbait_channel.hpp includes/informative_channel.hpp includes/location.hpp includes/news_agent.hpp includes/news_channel.hpp includes/news.hpp src/clickbait_channel.cc src/informative_channel.cc src/location.cc src/news_agent.cc src/news_channel.cc
	${CXX} ${CXX_FLAGS} src/main.cc src/clickbait_channel.cc src/informative_channel.cc src/location.cc src/news_agent.cc src/news_channel.cc -o bin/exec

bin/tests: tests/tests.cc includes/clickbait_channel.hpp includes/informative_channel.hpp includes/location.hpp includes/news_agent.hpp includes/news_channel.hpp includes/news.hpp src/clickbait_channel.cc src/informative_channel.cc src/location.cc src/news_agent.cc src/news_channel.cc
	${CXX} ${CXX_FLAGS} tests/tests.cc src/clickbait_channel.cc src/informative_channel.cc src/location.cc src/news_agent.cc src/news_channel.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*