CC=gcc
CFLAGS=-g
DEPS = pgm.h recognition.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: pgm.o main.o recognition.o
	$(CC) -o main pgm.o main.o recognition.o

clean:
	-rm *.o
