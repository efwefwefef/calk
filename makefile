all:
	g++ calk.cpp main.cpp -o out -std=c++11
test: tests
	./tests
tests: calk.cpp tests.cpp
	g++ tests.cpp calk.cpp -o tests -lgtest -lgtest_main -lpthread -std=c++11

