CXXFLAGS=-std=c++11 -Iinclude -Wall -Werror -g

all: bin/board.o bin/board_view.o bin/ncurses_view.o bin/main.o
	g++ $(CXXFLAGS) bin/board.o bin/board_view.o bin/ncurses_view.o bin/main.o -o main -lncurses

bin/board.o: src/board.cpp include/board.h | bin
	g++ $(CXXFLAGS) -c src/board.cpp -o bin/board.o

bin/board_view.o: src/board_view.cpp include/board_view.h include/board.h | bin
	g++ $(CXXFLAGS) -c src/board_view.cpp -o bin/board_view.o

bin/ncurses_view.o: src/ncurses_view.cpp include/board_view.h include/board.h | bin
	g++ $(CXXFLAGS) -c src/ncurses_view.cpp -o bin/ncurses_view.o

bin/main.o: src/main.cpp include/board.h include/board_view.h | bin
	g++ $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/test.o: test/test.cpp include/test.h | bin
	g++ $(CXXFLAGS) -c test/test.cpp -o bin/test.o

bin/board_test.o: test/board_test.cpp include/board_test.h include/board.h | bin
	g++ $(CXXFLAGS) -c test/board_test.cpp -o bin/board_test.o

bin:
	mkdir bin

board_test: bin/board.o bin/test.o bin/board_test.o
	g++ $(CXXFLAGS) bin/board.o bin/test.o bin/board_test.o -o board_test

clean:
	rm -rf bin main board_test
