CXXFLAGS = -O2 -Wall -Werror -pedantic -std=c++11 -Iinclude -Itest -g

all: bin/bitstream.o bin/tree.o bin/huffman.o bin/main.o | bin
	g++ $(CXXFLAGS) bin/bitstream.o bin/tree.o bin/huffman.o bin/main.o -o bin/huffman

test: bin/bitstream.o bin/tree.o bin/huffman.o bin/autotest.o bin/huffman_test.o bin/test.o | bin
	g++ $(CXXFLAGS) bin/bitstream.o bin/tree.o bin/huffman.o bin/autotest.o bin/huffman_test.o bin/test.o -o bin/test

bin/bitstream.o: src/bitstream.cpp include/bitstream.h | bin
	g++ $(CXXFLAGS) -c src/bitstream.cpp -o bin/bitstream.o

bin/tree.o: src/tree.cpp include/tree.h | bin
	g++ $(CXXFLAGS) -c src/tree.cpp -o bin/tree.o

bin/huffman.o: src/huffman.cpp include/huffman.h include/tree.h | bin
	g++ $(CXXFLAGS) -c src/huffman.cpp -o bin/huffman.o

bin/main.o: src/main.cpp include/huffman.h | bin
	g++ $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/autotest.o: test/autotest.cpp test/autotest.h | bin
	g++ $(CXXFLAGS) -c test/autotest.cpp -o bin/autotest.o

bin/huffman_test.o: test/huffman_test.cpp test/huffman_test.h include/huffman.h | bin
	g++ $(CXXFLAGS) -c test/huffman_test.cpp -o bin/huffman_test.o

bin/test.o: test/test.cpp test/huffman_test.h | bin
	g++ $(CXXFLAGS) -c test/test.cpp -o bin/test.o

bin:
	mkdir bin

clean:
	rm -rf bin