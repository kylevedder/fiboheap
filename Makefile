
all: custom_test.cc
	clang++ -std=c++11 -Wall -Werror -o3 custom_test.cc -g -o test_fiboheap

