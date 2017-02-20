#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"
#include "mymalloc.c"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define LENGTH 3000

int testA(){
	int total = 0, counter = 0;
	while (counter < 100){
		clock_t start = clock(), diff;
		char * a[3000];
		int i =0;
		for (;i<3000;i++){
			a[i] = (char *) malloc(1);
			if (a[i] == NULL){
				return -1;
			}
		}
		i =0;
		for (;i<3000;i++){
			free(a[i]);
		}
		diff = clock() - start;
		total+=diff;
		counter++;
	}
	return total/100;
}
int testB(){
	int total = 0, counter = 0;
	while (counter < 100){
		clock_t start = clock(), diff;
		int i = 0;
		for(;i < 3000; i++){
			char * a = (char *) malloc(sizeof(char));
			free(a);
		}
		diff = clock() - start;
		total += diff;
		counter++;
	}

	return total/100;
	
}
int testC(){
	int total = 0, counter = 0;
	char * a[LENGTH];
	srand(time(NULL));
	while (counter < 100){
		clock_t start = clock(), diff;

		int r = rand() % 10, i = 0, freeIndex = 0, mallocIndex = 0; 

		while (i < 2*LENGTH){
			if (mallocIndex == LENGTH){
				if (freeIndex < LENGTH){
					free(a[freeIndex++]);
				}
			}
			else if (freeIndex >= mallocIndex){
				if (mallocIndex < LENGTH){
					a[mallocIndex++] = (char *) malloc(1);
					if (a[mallocIndex-1] == NULL){
						printf("Malloc ran out of space.\n");
						exit(1);
					}
				}
			} else if (r > 4){
				if (mallocIndex < LENGTH){
					a[mallocIndex++] = (char *) malloc(1);
					if (a[mallocIndex-1] == NULL){
						printf("Malloc ran out of space.\n");
						exit(1);
					}
				}
			}
			else{
				if (freeIndex < LENGTH){
					free(a[freeIndex++]);
				}
			}
			r = rand() % 10;
			i++;
		}
		diff = clock() - start;
		total += diff;
		counter++;
	}
	return total/100;
}

int testD(){
	int total = 0, counter = 0;
	char * a[LENGTH];
	int freeSpace = SIZE - 4;
	srand(time(NULL));
	while (counter < 100){
		clock_t start = clock(), diff;
		int r = (rand() % 100) + 1, i = 0, freeIndex = 0, mallocIndex = 0; 
		while (i < 2*LENGTH){
			if (mallocIndex == LENGTH || freeSpace <= 6){
				if (freeIndex < LENGTH){
					int * temp = (int *) (a[freeIndex]-4);
					freeSpace += 4 + (*temp & ~1);
					free(a[freeIndex++]);
				}
			}
			else if (freeIndex >= mallocIndex){
				if (mallocIndex < LENGTH){
					int toMalloc = (r+4) < freeSpace ? r : freeSpace-4;
					a[mallocIndex++] = (char *) malloc(toMalloc);
					freeSpace -= (r + 4);
					if (a[mallocIndex-1] == NULL){
						printf("malloc ran out of space.");
						exit(1);
					}
				}
			} else if (r > 50){
				if (mallocIndex < LENGTH){
					int toMalloc = (r+4) < freeSpace ? r : freeSpace-4;
					a[mallocIndex++] = (char *) malloc(toMalloc);
					freeSpace -= ((r & ~1) + 4);
					if (a[mallocIndex-1] == NULL){
						printf("malloc ran out of space.");
						exit(1);
					}
				}
			}
			else{
				if (freeIndex < 3000){
					int * temp = (int *) (a[freeIndex]-4);
					freeSpace += 4 + (*temp & ~1);
					free(a[freeIndex++]);
				}
			}
			r = (rand() % 100) + 1;
			i++;
		}
		diff = clock() - start;
		total += diff;
		counter++;
	}
	return total/100;
}
int testE(){
	int total = 0, counter = 0;
	char * a[3000];
	while (counter < 100){
		clock_t start = clock(), diff;
		int r = rand() % 2, mallocIndex = 0, amount_malloc = 0;
		while (amount_malloc < 10000){
			if(r == 1){
				int toMalloc = 10;
				a[mallocIndex++] = (char*) malloc(toMalloc);
				if (a[mallocIndex-1] == NULL){
					return -1;
				}
				amount_malloc+= 10;
			}
			else{
				int toMalloc = 100;
				a[mallocIndex++] = (char*) malloc(toMalloc);
				if (a[mallocIndex-1] == NULL){
					return -1;
				}
				amount_malloc+= 100;
			}
			r = rand() % 2;
		}
		int freeindex = 0;
		while(freeindex < mallocIndex){
			free(a[freeindex]);
			freeindex++;
		}
		diff = clock() - start;
		total += diff;
		counter++;
	}
	return total/100;
}
int testF(){
	int total = 0, counter = 0;
	char * a[3000];
	while (counter < 100){
		clock_t start = clock(), diff;
		int mallocIndex = 0, amount_malloc = 0;
		while (amount_malloc < 3000){
			a[mallocIndex++] = (char*) malloc(10);
			if (a[mallocIndex-1] == NULL){
				return -1;
			}
			amount_malloc+= 10;
		}
		int freeindex = 0;
		while(freeindex < mallocIndex){
			free(a[freeindex]);			
			freeindex+=2;
		}
		while(amount_malloc < 5000){
			a[mallocIndex++] = (char*) malloc(11);
			if (a[mallocIndex-1] == NULL){
				return -1;
			}
			amount_malloc+=11;
		}
		int freeindex_2 = 1;
	
		while(freeindex_2 < freeindex){
			free(a[freeindex_2]);
			freeindex_2 += 2;
		}
		freeindex_2--;
		while(freeindex_2 < mallocIndex){
			free(a[freeindex_2]);
			freeindex_2++;		
		}
		diff = clock() - start;
		total += diff;
		counter++;
	}
	return total/100;
	
}
int main(){
	printf("TestA's average time was %d microseconds\n", testA());
	printf("TestB's average time was %d microseconds\n", testB());
	printf("TestC's average time was %d microseconds\n", testC());
	printf("TestD's average time was %d microseconds\n", testD());
	printf("TestE's average time was %d microseconds\n", testE());
	printf("TestF's average time was %d microseconds\n", testF());
	return 0;
}