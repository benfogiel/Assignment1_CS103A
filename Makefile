main: main.o block.o
	g++ -g -Wall -std=c++11 main.o block.o -o main -lssl -lcrypto
	#g++ -g -Wall -std=c++11 -o main main.cpp -L/usr/local/opt/openssl@1.1/lib -lcrypto


main.o: main.cpp
	g++ -c main.cpp

block.o: block.cpp
	g++ -c block.cpp

clean:
	rm -f main main.o block.o
