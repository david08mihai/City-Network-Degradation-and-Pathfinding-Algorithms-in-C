CC=gcc
CFLAGS=-Wall -g

build: main

main: tema3.o cerinta1.o cerinta2.o
	$(CC) $(CFLAGS) tema3.o cerinta1.o cerinta2.o -o tema3

tema3.o: tema3.c cerinta1.h cerinta2.h
	$(CC) $(CFLAGS) -c tema3.c -o tema3.o

cerinta1.o: cerinta1.c cerinta1.h 
	$(CC) $(CFLAGS) -c cerinta1.c -o cerinta1.o

ceromta2.o: cerinta2.c cerinta2.h
	$(CC) $(CFLAGS) -c cerinta2.c -o cerinta2.o
run:
	./tema3

clean:
	rm -f tema3 *.o
