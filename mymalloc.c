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
	int oldValue = *p == 0 ? SIZE : *p;
	// printf("SPLIT p = %d\n", *p);
	// printf("SPLIT bOrO = %d\n", bytesOrOne);
	// printf("toAdd =  %d\n", toAdd);
	// printf("oldValue =  %d\n", oldValue);
	*p = bytesOrOne;
	void * toReturn = (void *) p+4;
	int * p1 = (int *) (&myblock[(toAdd + 4 + bytesOrOne - 1)]);
	int newValue = (oldValue - (4 + bytesOrOne));
	if (newValue % 2 == 1){
		newValue++;
	}
	*p1 = newValue;
	// printf("newValue =  %d\n", newValue);
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
		else if (*p > bytes){
			return split(p,bytesOrOne, toAdd);
		}
	}
	return NULL;
}

void myfree(void * toFree, char * file, int line){
	int * p = (int *) ((toFree-4));
	if (*p == 0){
		printf("ERROR YOUR FREEING SHIT YOU DONT HAVE\n");
		return;
	}
	*p = *p - 1;
	int * nextone = (int *) ((toFree-4) + (*p + 4)); //(p+(*p+4));
	printf("next p = %d\n", (*p+4)); //myblock[12]
	printf("next one = %d\n", *nextone); //myblock[32]
	if ((*nextone & 1) != 1){
		int newInt = (*p);
		if (newInt % 2 != 0){
			newInt++;
		}
		*p = newInt;
		*nextone = 0;
	}
}
int main(){
	char * a = malloc(8);
	printf("a=%d\n", (a-6295648));
	char * b = malloc(15);
	printf("b=%d\n", (b-6295648));
	char * c = malloc(15);
	printf("c=%d\n", (c-6295648));
	char * d = malloc(30);
	printf("d=%d\n", (d-6295648));
	int * p1 = (int*)(&myblock[32]);
	printf("p1=%d\n", *p1);
	int * p = (int*)(&myblock[0]);
	int toAdd = 0;
	while((void *)p < (void *)&myblock[SIZE] && *p != 0){
		printf("%d\n", *p);	
		int oldValue = *p;
		if (oldValue % 2 == 1){
			oldValue--;
		}
		printf("looking at index %d\n", (toAdd + oldValue + 4));
		p = (int *) (&myblock[(toAdd + oldValue + 4)]);
		toAdd += oldValue + 4;
	}
	free(b);
	p = (int*)(&myblock[0]);
	toAdd = 0;
	while((void *)p < (void *)&myblock[SIZE] && *p != 0){
		printf("%d\n", *p);	
		int oldValue = *p;
		if (oldValue % 2 == 1){
			oldValue--;
		}
		printf("looking at index %d\n", (toAdd + oldValue + 4));
		p = (int *) (&myblock[(toAdd + oldValue + 4)]);
		toAdd += oldValue + 4;
	}
	char * basfa = malloc(7);
	p = (int*)(&myblock[0]);
	toAdd = 0;
	while((void *)p < (void *)&myblock[SIZE] && *p != 0){
		printf("%d\n", *p);	
		int oldValue = *p;
		if (oldValue % 2 == 1){
			oldValue--;
		}
		printf("looking at index %d\n", (toAdd + oldValue + 4));
		p = (int *) (&myblock[(toAdd + oldValue + 4)]);
		toAdd += oldValue + 4;
	}
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