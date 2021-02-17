main: main.o pgm.o recognition.o
	gcc -o main main.o pgm.o recognition.o

main.o: main.c
	gcc -o main.o -c main.c -Wall

pgm.o: pgm.c
	gcc -o pgm.o -c pgm.c -Wall

recognition.o: recognition.c
	gcc -o recognition.o -c recognition.c -Wall

clean:
	rm -f *.o core

rmproper:
	rm -f main
