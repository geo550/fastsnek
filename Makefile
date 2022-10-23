snake: main.cpp grid.hpp
	g++ main.cpp -o snake -lncurses

build:
	g++ main.cpp -o snake -lncurses
run: main.cpp grid.hpp
	./snake
