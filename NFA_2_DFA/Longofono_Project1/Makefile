CC = g++
CXXFLAGS = -Wall -g -std=c++11

all: main

main: n2d.cpp helpers.h
	$(CC) $(CXXFLAGS) n2d.cpp -o main

test:
	./main < input1.txt

clean:
	rm -f *.o main
