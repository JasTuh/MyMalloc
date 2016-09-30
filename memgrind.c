#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "mymalloc.c"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
#define SIZE 5000


int testA(){
	char * a[50];
	int i =0;
	for (;i<50;i++){
		a[i] = (char *) malloc(1);
		printf("a[%d]=%d\n", i,(a[i] - 6295648));
	}
	int * p = (int *) (a[0]-4);
	printf("%d\n", *p);
	free(a[0]);
	p = (int *) (a[1]-4);
	printf("a[1] = %d\n", *p);
	free(a[1]);
	p = (int *) (a[1]-4);
	printf("a[1] = %d\n", *p);
	p = (int *) (a[0]-4);
	printf("%d\n", *p);
	return 0;
}
int main(){
	printf("%d\n", testA());
	// char * a = malloc(8);
	// printf("a=%d\n", (a-6299744));
	// char * b = malloc(15);
	// printf("b=%d\n", (b-6299744));
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