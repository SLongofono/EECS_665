CC = g++
CXXFLAGS = -Wall -g -std=c++11

all: main

main: State.o n2d.cpp
	$(CC) $(CXXFLAGS) State.o n2d.cpp -o main

state: State.cpp
	$(CC) $(CXXFLAGS) -c -o State.o State.cpp

clean:
	rm -f *.0 main
