CPP_FLAGS=-Werror -Wall -std=c++11

bin/mergesort: bin/mergesort.o bin/main.o
	g++ $(CPP_FLAGS) bin/main.o bin/mergesort.o -o bin/mergesort

bin/mergesort.o: src/mergesort.cpp src/mergesort.h
	g++ $(CPP_FLAGS) -c src/mergesort.cpp -o bin/mergesort.o

bin/main.o: src/main.cpp src/mergesort.h
	g++ $(CPP_FLAGS) -c src/main.cpp -o bin/main.o



