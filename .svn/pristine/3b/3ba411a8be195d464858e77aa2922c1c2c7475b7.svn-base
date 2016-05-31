CPP_FLAGS=-Werror -Wall -std=c++11 -g

all: bin/huffman

bin/huffman: bin/encode.o bin/compress.o bin/decode.o bin/huffman_archive.o bin/main.o
	g++ $(CPP_FLAGS) bin/encode.o bin/compress.o bin/main.o bin/decode.o bin/huffman_archive.o -o bin/huffman

bin/encode.o: src/encode.cpp src/encode.h src/huffman.h
	g++ $(CPP_FLAGS) -c src/encode.cpp -o bin/encode.o

bin/decode.o: src/decode.cpp src/decode.h src/huffman.h
	g++ $(CPP_FLAGS) -c src/decode.cpp -o bin/decode.o

bin/compress.o: src/compress.cpp src/compress.h src/encode.h
	g++ $(CPP_FLAGS) -c src/compress.cpp -o bin/compress.o

bin/huffman_archive.o: src/huffman_archive.cpp src/huffman_archive.h src/compress.h src/decode.h src/encode.h
	g++ $(CPP_FLAGS) -c src/huffman_archive.cpp -o bin/huffman_archive.o

bin/main.o: src/main.cpp src/huffman_archive.h src/compress.h src/decode.h
	g++ $(CPP_FLAGS) -c src/main.cpp -o bin/main.o
