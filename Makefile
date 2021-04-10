main.o: main.cpp
	g++ -c main.cpp

block.o: block.cpp
	g++ -c block.cpp

main: main.o block.o
	g++ main.o block.o -o main -lssl -lcrypto
