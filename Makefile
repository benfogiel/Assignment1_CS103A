main.o: main.cpp
	g++ -c main.cpp

cards.o: cards.cpp
	g++ -c cards.cpp

main: main.o cards.o
	g++ main.o cards.o -o main

testcards: testcards.cpp cards.cpp
	g++ testcards.cpp cards.cpp -o testcards