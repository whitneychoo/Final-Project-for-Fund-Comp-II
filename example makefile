all:	main

main: main.o whitney.o sam.o soyon.o jo.o
	g++ main.o whitney.o sam.o soyon.o jo.o -o main -Wall
	
main.o: main.cpp
	g++ -c main.cpp
	
whitney.o: whitney.cpp whitney.h
	g++ -c whitney.cpp whitney.h

etc.

clean:
	rm -f *.o main
