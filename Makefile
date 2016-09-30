CC = gcc
CCFLAGS = -Wall

all: mymalloc memgrind

mymalloc: mymalloc.c mymalloc.h
	$(CC) $(CCFLAGS) -g -o mymalloc mymalloc.c

memgrind: memgrind.c mymalloc.c mymalloc.h
	$(CC) $(CCFLAGS) -g -o memgrind memgrind.c

clean:
	rm memgrind