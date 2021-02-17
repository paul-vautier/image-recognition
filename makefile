CC=gcc
CFLAGS=-Wall -O
EXEC=main
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
	all: $(EXEC)
	main: $(OBJ)
									$(CC) -o
									$@ $^ $(LDFLAGS)
	main.o: pgm.h

	%.o: %.c
									$(CC) -o $@ -c $< $(CFLAGS)
	clean:
									rm -f *.o core
	mrproper: clean
									rm -f $(EXEC)
