#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define SIZE 5000

static char myblock[SIZE];

/*
THERES AN ERROR BECEAUSE IM NOT REFERING TO THE RIGHT INDEX BECAUSE IM NOT INCLUDING PAST ONES
*/
void * split(int * p, int bytesOrOne, int toAdd){
	*p = bytesOrOne;
	void * toReturn = (void *) p+4;
	int * p1 = (int *) (&myblock[(toAdd + 4 + bytesOrOne)]);
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
		return split(p,bytesOrOne,0);
	}
	int toAdd = 0;
	while((void *)p < (void *)&myblock[SIZE]){
		if ((*p & 1) == 1 || *p < bytes){
			int oldValue = *p;
			p = (int *) (&myblock[(toAdd+*p + 4)]);
			toAdd+=oldValue;
			
		}
		else if (*p > bytes){
			printf("ta=%d\n", toAdd);
			return split(p,bytesOrOne, toAdd);
		}
	}
	return NULL;
}

void myfree(void * toFree, char * file, int line){
	int * p = (int *) (toFree-4);
	printf("p=%d\n", *p);
	if (*p == 0){
		printf("ERROR YOUR FREEING SHIT YOU DONT HAVE\n");
		return;
	}
	int * nextone = (int *) (&myblock[*p+4]);
	if ((*nextone & 1) != 1){
		int newInt = (*p + *nextone + 4);
		if (newInt % 2 != 0){
			newInt++;
		}
		*p = newInt;
		*nextone = 0;
	}else{
		*p = (*p)-1;
	}
}
int main(){
	char * a = malloc(8);
	printf("a=%d\n", a);
	char * b = malloc(15);
	printf("b=%d\n", b);
	char * c = malloc(15);
	printf("c=%d\n", c);
	int * p = (int*)(&myblock[0]);
	while((void *)p < (void *)&myblock[SIZE] && *p != 0){
		printf("%d\n", *p);	
		printf("looking at index %d\n", (*p + 4));
		p = (int *) (&myblock[(*p + 4)]);
	}
	p = (int*)(&myblock[30]);
	printf("thingy=%d\n", *p);
	// free(b);
	// printf("sep\n");
	// p = (int*)(&myblock[0]);
	// while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// 	printf("%d\n", *p);	
	// 	p = (int *) (&myblock[((*p|1) + 4)]);
	// }
	// b = malloc(15);
	// printf("sep\n");
	// p = (int*)(&myblock[0]);
	// while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// 	printf("%d\n", *p);	
	// 	p = (int *) (&myblock[((*p|1) + 4)]);
	// }
	return 0;
}