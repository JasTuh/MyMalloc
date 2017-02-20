#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define SIZE 25000

static char myblock[SIZE];

void * split(int * p, int bytesOrOne, int toAdd){
	if (*p == (bytesOrOne-1)){
		*p = bytesOrOne;
		void * toReturn = ((void *)p)+4;
		return toReturn;
	}

	if (*p != 0 && (*p)-6 <= (bytesOrOne-1)){
		*p += 1;
		void * toReturn = ((void *)p)+4;
		return toReturn;
	}
	int oldValue = *p == 0 ? (SIZE-4) : *p;
	*p = bytesOrOne;
	// printf("setting memory address %d to %d\n", p, bytesOrOne);

	void * toReturn = ((void *)p)+4;
	int * p1 = (int *) (&myblock[(toAdd + 4 + bytesOrOne - 1)]);

	int newValue = (oldValue - (4 + (bytesOrOne - 1)));
	// printf("FUCK THOMAS %d AND %d AND %d\n", (toAdd + 4 + bytesOrOne - 1), newValue, (toAdd + 4 + bytesOrOne - 1) - (bytesOrOne - 1));
	// printf("*p = %d \n", *p);
	// if (newValue <= 0){ //was <= 1
	// 	*p += (toAdd + 4 + bytesOrOne - 1) - (bytesOrOne - 1);
	// 	return toReturn;	
	// }
	// else{ 
		// printf("setting memory address %d to %d\n", p1, newValue);
		*p1 = newValue;
	// }
	return toReturn;
}

void * mymalloc(int bytes, char * file, int line){
	if (bytes % 2 == 1){bytes++;}
	if (bytes == 0){
		return NULL;
	}
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
	// printf("%s made this function error on line %d\n", file, line);
	return NULL;
}
/**
 *
 **/
void combine(){
	int * current = (int*)(&myblock[0]);
	int * prev = NULL;
	int toAdd = 0;
	// printHeap();
	int callAgain = 0;
	while((void *)current < (void *)&myblock[SIZE] && *current != 0){	
		int currentValue = *current;
		int prevValue = prev == NULL ? 1:*prev;
		if (currentValue % 2 == 0 && (prevValue % 2 == 0)){
			*prev = currentValue+prevValue + 4;
			current = (void *)(&myblock[(toAdd + currentValue + 4)]);
			callAgain = 1;
			break;
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
	if (callAgain){
		combine();
	}
}

/** 
 * Prints the implicit list in malloc.
 **/
void printHeap(){
	int * p = (int*)(&myblock[0]);
	int toAdd = 0;
	while ((void *)p < (void *)&myblock[SIZE-1] && *p != 0){		
		int oldValue = *p;
		printf("found a %d at %li\n", *p, ((void *)p - (void *)&myblock[0]));
		p = (int *) (&myblock[(toAdd+(oldValue&~1) + 4)]);
		toAdd+=(oldValue&~1)+4;
	}
}
//add going through the list 
void myfree(void * toFree, char * file, int line){
	if (toFree < (void *) &myblock[0] || toFree > (void *) &myblock[SIZE-1]){
		printf("ERROR: pointer given to free from file %s at line %d caused free to error\n", file, line);
		exit(1);
	}
	int * p = (int *) ((toFree-4));
	if (*p == 0){
		printf("ERROR: pointer given to free from file %s at line %d caused free to error\n", file, line);
		exit(1);
	}
	if (*p % 2 == 0){
		printf("ERROR: pointer given to free from file %s at line %d was already free\n", file, line);
		exit(1);
	}
	*p = *p - 1;
	combine();
}