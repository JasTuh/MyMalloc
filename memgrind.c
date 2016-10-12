#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"
#include "mymalloc.c"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define MEMES 3000

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
	char * a[MEMES];
	srand(time(NULL));
	while (counter < 100){
		clock_t start = clock(), diff;

		int r = rand() % 10, i = 0, freeIndex = 0, mallocIndex = 0; 

		while (i < 2*MEMES){
			if (mallocIndex == MEMES){
				if (freeIndex < MEMES){
					int * temp = (int *) (a[freeIndex]-4);
					// printf("freeing %d\n", *temp);
					free(a[freeIndex++]);
				}
			}
			else if (freeIndex >= mallocIndex){
				if (mallocIndex < MEMES){
					a[mallocIndex++] = (char *) malloc(1);
					if (a[mallocIndex-1] == NULL){
						// printf("Malloc ran out of space.\n");
						exit(1);
					}
				}
			} else if (r > 4){
				if (mallocIndex < MEMES){
					a[mallocIndex++] = (char *) malloc(1);
					if (a[mallocIndex-1] == NULL){
						// printf("Malloc ran out of space.\n");
						exit(1);
					}
				}
			}
			else{
				if (freeIndex < MEMES){
					int * temp = (int *) (a[freeIndex]-4);
					// printf("freeing %d\n", *temp);
					free(a[freeIndex++]);
				}
			}
			r = rand() % 10;
			i++;
			// printHeap();
		}
		diff = clock() - start;
		total += diff;
		counter++;
		// printf("ASDFASDF:LKASDFL:KASDF:ADSFASDFASDFADSFADSF\n");
	}
	return total/100;
}
long int test_c(){
	char* saved[3000];
	int count = 0;
	int pos = 0;
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	int i = 0;
	while (i < 6000){
		int random = rand() % 10;
		if(random < 5){
			saved[pos] = malloc(1);
			pos++;
			count++;
		}else{
			if(pos != 0){
				free(saved[pos-1]);
				pos--;
			}
		}
		if(count == 3000){
			break;
		}
		i++;
	}
	int diff = 3000-count;
	if(diff != 0){
		for(i = 0;i<diff;i++){
			saved[pos] = malloc(1);
			pos++;
		}
	}
	pos--;
	while(pos >= 0){
		free(saved[pos]);
		pos--;
	}
	gettimeofday(&end, NULL);
	long int total = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	return total;
}

int testD(){
	int total = 0, counter = 0;
	char * a[MEMES];
	int freeSpace = SIZE - 4;
	srand(time(NULL));
	while (counter < 100){
		// printf("ASDFJASLKFJADSLKFJASDFLKJ\n");
		clock_t start = clock(), diff;
		int r = (rand() % 100) + 1, i = 0, freeIndex = 0, mallocIndex = 0; 
		while (i < 2*MEMES){
			// printf("mallocing %d and freespace %d\n", r, freeSpace);
			if (mallocIndex == MEMES || freeSpace <= 6){
				if (freeIndex < MEMES){
					int * temp = (int *) (a[freeIndex]-4);
					// printf("freeing %d\n", *temp);
					freeSpace += 4 + (*temp & ~1);
					free(a[freeIndex++]);
				}
			}
			else if (freeIndex >= mallocIndex){
				if (mallocIndex < MEMES){
					int toMalloc = (r+4) < freeSpace ? r : freeSpace-4;
					// printf("mallocing %d\n", toMalloc);
					a[mallocIndex++] = (char *) malloc(toMalloc);
					freeSpace -= (r + 4);
					if (a[mallocIndex-1] == NULL){
						printf("malloc ran out of space.");
						exit(1);
					}
				}
			} else if (r > 50){
				if (mallocIndex < MEMES){
					int toMalloc = (r+4) < freeSpace ? r : freeSpace-4;
					// printf("mallocing %d\n", toMalloc);
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
					// printf("freeing %d\n", *temp);
					free(a[freeIndex++]);
				}
			}
			r = (rand() % 100) + 1;
			i++;
			// printHeap();
		}
		diff = clock() - start;
		total += diff;
		counter++;
	}
	return total/100;
}
int main(){
	// int total = 0;
	// int i = 0;
	// for (; i < 100; i++)
	// 	total+=test_c();
	// printf("%d\n", total/100);
	// printHeap();
	printf("%d\n", testA());
	printHeap();
	printf("%d\n", testB());
	printHeap();
	printf("%d\n", testC());
	printHeap();
	printf("%d\n", testD());
	printHeap();
	// printHeap();
	// printHeap();
	// int total = 0;
	// int i = 0;
	// for (;i<100000;i++){
	// 	total += testD();
	// 	if (i % 50 == 0){
	// 		printHeap();
	// 	}
	// 	printf("%d\n", i);
	// }
	// printf("%d\n", total/100000);
	// char* saved[10];
	// int i;
	// srand(time(NULL));
	// for (i = 0; i < 10; i++){
	// 	int random = (rand() % 10)+1;
	// 	saved[i] = malloc(random);
	// }
	// printf("1\n");
	// printHeap();
	// for(i = 0;i < 10; i+=2){
	// 	free(saved[i]);
	// }
	// printf("2\n");
	// printHeap();
	// for (i = 0; i < 10; i+=2){
	// 	int random = (rand() % 20)+8;
	// 	printf("%d\n", random);
	// 	saved[i] = malloc(random);
	// }
	// printf("3\n");
	// printHeap();
	// for (i = 0; i < 10; i+=2){
	// 	free(saved[i]);
	// }
	// printf("4\n");
	// printHeap();
	char * a[10];
	printf("1\n");
	printHeap();
	a[0] = malloc(64);
	a[1] = malloc(83);
	a[2] = malloc(85);
	printf("1\n");
	printHeap();
	free(a[0]);
	printf("2\n");
	printHeap();
	a[3] = malloc(61);
	printHeap();
	// free(a[0]);
	// printf("2\n");
	// printHeap();
	// a[3] = malloc(2);
	// printHeap();
	// free(a[1]);
	// printf("2\n");
	// printHeap();
	// a[3] = malloc(99);
	// printf("3\n");
	// printHeap();
	// printf("2\n");
	// printHeap();
	// a[1] = malloc(66);
	// printf("3\n");
	// printHeap();
	// a[2] = malloc(98);
	// printf("4\n");
	// printHeap();
	// free(a[0]);
	// printf("4.5\n");
	// printHeap();
	// a[3] = malloc(1);
	// free(a[1]);
	// free(a[2]);
	// printf("5\n");
	// printHeap();
	// printf("hopefully freezes\n");
	// free(a[1]);
	// printf("after freezes\n");
	// printHeap();
	// free(a[3]);
	// printHeap();


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