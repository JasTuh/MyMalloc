#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define SIZE 5000

static char myblock[SIZE];

void * split(int * p, int bytesOrOne, int toAdd){
	int oldValue = *p == 0 ? (SIZE-4) : *p;
	*p = bytesOrOne;
	void * toReturn = (void *) p+4;
	int * p1 = (int *) (&myblock[(toAdd + 4 + bytesOrOne - 1)]);
	int newValue = (oldValue - (4 + (bytesOrOne - 1)));
	if (newValue < 0){
		*p += 2;
		return toReturn;	
	}
	else{ 
		*p1 = newValue;
	}
	return toReturn;
}

void * mymalloc(int bytes, char * file, int line){
	if (bytes % 2 == 1){bytes++;}
	int * p = (int *) (&myblock[0]);
	int bytesOrOne = (bytes | 1);
	if (*p == 0){
		return split(p,bytesOrOne,0);
	}
	int toAdd = 0;
	while((void *)p < (void *)&myblock[SIZE]){
		if ((*p & 1) == 1 || *p < bytes){
			int oldValue = *p;
			if (oldValue % 2 == 1){
				oldValue--;
			}
			p = (int *) (&myblock[(toAdd+oldValue + 4)]);
			toAdd+=oldValue+4;
			
		}
		else if (*p >= bytes){
			return split(p,bytesOrOne, toAdd);
		}
	}
	printf("%s made this function error on line %d\n", file, line);
	return NULL;
}
void combine(){
	int * current = (int*)(&myblock[0]);
	int * prev = NULL;
	int toAdd = 0;
	while((void *)current < (void *)&myblock[SIZE] && *current != 0){	
		int currentValue = *current;
		int prevValue = prev == NULL ? 1:*prev;
		if (currentValue % 2 == 0 && (prevValue % 2 == 0)){
			*prev = currentValue+prevValue + 4;
			current = (void *)(&myblock[(toAdd + currentValue + 4)]);
		}
		else{
			prev = current;
			if (currentValue %2 == 1){
				currentValue--;
			}
			current = (int *) (&myblock[(toAdd + (currentValue) + 4)]);
			toAdd += currentValue + 4;
		}

	}
}
void printHeap(){
	int * p = (int*)(&myblock[0]);
	int i = 0;
	for (; i < 100; i++){
		p = (int *) (&myblock[i]);
		if (*p != 0){
			printf("found a %d at %d\n", *p, i);
		}
	}
}
void myfree(void * toFree, char * file, int line){
	int * p = (int *) ((toFree-4));
	if (*p == 0){
		printf("ERROR YOUR FREEING SHIT YOU DONT HAVE\n");
		return;
	}
	*p = *p - 1;
	combine();
}