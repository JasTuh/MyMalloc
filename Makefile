CC = gcc
CCFLAGS = -Wall

all: mymalloc

mymalloc: mymalloc.c mymalloc.h
	$(CC) $(CCFLAGS) -g -o mymalloc mymalloc.c

clean:
	rm -rf *.o format calc