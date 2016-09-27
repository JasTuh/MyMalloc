#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )
static char myblock[5000];

void * mymalloc(int bytes){
	
}