CC=gcc
AR = ar
FLAGS=-Wall -g

all: frequency

frequency: main.o frequency.o
	$(CC) $(FLAGS) main.o frequency.o -o frequency

frequency.o: frequency.c 
	$(CC) $(FLAGS) -c frequency.c -o frequency.o

main.o: main.c 
	$(CC) $(FLAGS) -c main.c -o main.o 

.PHONY:clean all

clean:
	rm -f *.o frequency