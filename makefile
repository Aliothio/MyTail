all: tail


clean:
	rm -f tail *.o

tail: main.o tail.o
	gcc -Wall main.o tail.o -o tail

main.o: main.c tail.h
	gcc -c main.c

tail.o: tail.c tail.h
	gcc -c tail.c