#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"
#include "mymalloc.c"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define SIZE 25000


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
			// printf("a[%d]=%d\n", i,(a[i] - ((int) (a[0]-4)) ));
			// int * p = (int *) (a[i] - 4);
			// printf("a[%d]=%d\n", i, a[i]);
			// printf("p=%d\n", p);
			// printf("implicit int = %d\n", *p); //this should not be 0 :(

		}
		i =0;
		// int * value = (int *) (a[0]-4);
		for (;i<3000;i++){
			free(a[i]);
			// printf("a[%d]=%d\njust tried to free %d\n", 0, *value, i);
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
	char * a[3000];
	srand(time(NULL));
	while (counter < 100){
		clock_t start = clock(), diff;

		int r = rand() % 10, i = 0, freeIndex = 0, mallocIndex = 0; 

		while (i < 3000){
			if (mallocIndex == 3000){
				if (freeIndex < 3000){
					printf("before1\n");
					free(a[freeIndex++]);
					printf("after1\n");
				}
			}
			else if (freeIndex >= mallocIndex){
				if (mallocIndex < 3000){
					printf("before2\n");
					a[mallocIndex++] = (char *) malloc(1);
					if (a[mallocIndex-1] == NULL){
						printf("\n\nITS NULL\n\n\n");
					}
					printf("after2\n");
				}
			} else if (r > 4){
				if (mallocIndex < 3000){
					printf("before3\n");
					a[mallocIndex++] = (char *) malloc(1);
					if (a[mallocIndex-1] == NULL){
						printHeap();
						printf("\n\nITS NULL\n\n\n");
					}
					printf("after3\n");
				}
			}
			else{
				if (freeIndex < 3000){
					int * value = (int *) (a[freeIndex]-4);
					printf("before4 freeIndex = %d mallocIndex=%d and value = %d\n", freeIndex, mallocIndex, *value);
					free(a[freeIndex++]);
					value = (int *) (a[freeIndex-1]-4);
					printf("after4 value = %d\n", *value);
				}
			}
			r = rand() % 10;
			i++;
		}
		printf("counter = %d\n", counter);
		diff = clock() - start;
		// return diff;
		total += diff;
		counter++;
	}
	return total/100;
}
int main(){
	// printf("%d\n", testA());
	// printf("%d\n", testB());
	// printf("%d\n", testC());
	char * a[10];
	printf("1\n");
	printHeap();
	a[0] = malloc(1);
	printf("2\n");
	printHeap();
	a[1] = malloc(1);
	printf("3\n");
	printHeap();
	a[2] = malloc(1);
	printf("4\n");
	printHeap();
	a[3] = malloc(1);
	free(a[0]);
	free(a[2]);
	printf("5\n");
	printHeap();
	printf("hopefully freezes\n");
	free(a[1]);
	printf("after freezes\n");
	printHeap();
	// free(a[0]);
	// printf("5\n");
	// printHeap();
	// free(a[1]);
	// printf("6\n");
	// printHeap();
	// a[4] = malloc(1);
	// printf("7\n");
	// printHeap();
	// a[5] = malloc(1);
	// printf("8\n");
	// printHeap();
	// char * a = malloc(sizeof(char));
	// printf("a=%d\n", (a - 6295648));
	// char * b = malloc(15);
	// printf("b=%d\n", (b-6295648));
	// printf("\n\n");
	// printHeap();
	// free(b);
	// printf("\n\n");
	// printHeap();
	// free(a);
	// printf("\n\n\n");
	// printHeap();
	// char * c = malloc(15);
	// printf("c=%d\n", (c-6299744));
	// char * d = malloc(30);
	// printf("d=%d\n", (d-6299744));
	// int * p1 = (int*)(&myblock[32]);
	// printf("p1=%d\n", *p1);
	// int * p = (int*)(&myblock[0]);
	// int toAdd = 0;
	// while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// 	printf("%d\n", *p);	
	// 	int oldValue = *p;
	// 	if (oldValue % 2 == 1){
	// 		oldValue--;
	// 	}
	// 	printf("looking at index %d\n", (toAdd + oldValue + 4));
	// 	p = (int *) (&myblock[(toAdd + oldValue + 4)]);
	// 	toAdd += oldValue + 4;
	// }
	// free(b);
	// p = (int*)(&myblock[0]);
	// toAdd = 0;
	// while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// 	printf("%d\n", *p);	
	// 	int oldValue = *p;
	// 	if (oldValue % 2 == 1){
	// 		oldValue--;
	// 	}
	// 	printf("looking at index %d\n", (toAdd + oldValue + 4));
	// 	p = (int *) (&myblock[(toAdd + oldValue + 4)]);
	// 	toAdd += oldValue + 4;
	// }
	// char * basfa = malloc(7);
	// p = (int*)(&myblock[0]);
	// toAdd = 0;
	// while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// 	printf("%d\n", *p);	
	// 	int oldValue = *p;
	// 	if (oldValue % 2 == 1){
	// 		oldValue--;
	// 	}
	// 	printf("looking at index %d\n", (toAdd + oldValue + 4));
	// 	p = (int *) (&myblock[(toAdd + oldValue + 4)]);
	// 	toAdd += oldValue + 4;
	// }
	// char * b3 = malloc(2);
	// printf("b3=%d\n", (b3-6299744));
	// p = (int*)(&myblock[0]);
	// toAdd = 0;
	// while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// 	printf("%d\n", *p);	
	// 	int oldValue = *p;
	// 	if (oldValue % 2 == 1){
	// 		oldValue--;
	// 	}
	// 	printf("looking at index %d\n", (toAdd + oldValue + 4));
	// 	p = (int *) (&myblock[(toAdd + oldValue + 4)]);
	// 	toAdd += oldValue + 4;
	// }
	// // free(b);
	// // printf("sep\n");
	// // p = (int*)(&myblock[0]);
	// // while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// // 	printf("%d\n", *p);	
	// // 	p = (int *) (&myblock[((*p|1) + 4)]);
	// // }
	// // b = malloc(15);
	// // printf("sep\n");
	// // p = (int*)(&myblock[0]);
	// // while((void *)p < (void *)&myblock[SIZE] && *p != 0){
	// // 	printf("%d\n", *p);	
	// // 	p = (int *) (&myblock[((*p|1) + 4)]);
	// // }
	return 0;
}