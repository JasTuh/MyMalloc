#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define SIZE 5000

static char myblock[SIZE];


void * split(int * p, int bytesOrOne){
	*p = bytesOrOne;
	void * toReturn = (void *) p+4;
	int * p1 = (int *) (&myblock[(4 + bytesOrOne)]);
	int newValue = (SIZE - (8 + bytesOrOne));
	if (newValue % 2 == 1){
		newValue++;
	}
	*p1 = newValue;
	return toReturn;
}

void * mymalloc(int bytes, char * file, int line){
	if (bytes % 2 == 1){bytes++;}
	int * p = (int *) (&myblock[0]);
	int bytesOrOne = (bytes | 1);
	if (*p == 0){
		return split(p,bytesOrOne);
	}
	while((void *)p < (void *)&myblock[SIZE]){
		if ((*p & 1) == 1 || *p < bytes){
			p = (int *) (&myblock[(*p + 4)]);
		}
		else if(*p > bytes){
			return split(p,bytesOrOne);
		}
	}
	return NULL;
}

void free(void * p){
	int * p = (int *) (&myblock[p-4]);
	if (p == 0){
		printf("ERROR YOUR FREEING SHIT YOU DONT HAVE\n");
		return;
	}

}
int main(){
	char * a = malloc(8);
	// int * intlocation = (int*)(&myblock[13]);
	// printf("%d\n", *intlocation);	
	char * b = malloc(15);
	// int * intlocation = (int*)(&myblock[13]);
	// printf("%d\n", *intlocation);	
	char * c = malloc(2000);
	int * p = (int*)(&myblock[0]);
	while((void *)p < (void *)&myblock[SIZE] && *p != 0){
		printf("%d\n", *p);	
		p = (int *) (&myblock[(*p + 4)]);
	}
	return 0;
}