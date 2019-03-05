//
// Created by viraj on 2/11/2019.
//

/* Stack x1000
 *
 *
 * Heap
 *
 *
 * Code
 *
 *
 * Data
 *
 *
 * x0000
 *
 *
 */
/*
 * How to figure out if stack goes up or down?
 * -> define 2 local variable and compare addresses of local variables
 * if local variables are at decreasing addresses than u know the direction
 *
 *
 * Stack frame:
 * Arguments
 * Ret
 * Base pointer-> way to access arguments/local
 * Stack pointer
 * Local
 *
 * once you are done stackframe is deleted from stack memory
 *
 * Stack has limited size
 * small piece of memory
 * just a couple of megabytes
 *
 * If you invoke the same function it creates a new stack frame
 * eventually it will crash
 *
 * Easy for user
 * very fast
 *
 * Heap -> blob of memory tightly managed by cpu
 * Ask to get this memory space
 * requires more user management
 * Heap variables are essentially global variables
 * Much larger than stack
 * program can ask for more space if possible
 *
 * Malloc
 * Calloc
 * Realloc
 * Free
 * ...
 *
 * After Malloc is called memory is not initilized
 * Calloc initilzed every element to 0;
 * Calloc is slower than malloc
 *
 * NULL is returned if allocation is not successful
 *
 * Realloc
 * extends space
 * if cannot extend moves to another place
 * p usually wil not point to same place
 *
 */
#include <stdlib.h>

int* fun(){
    int *p = (int*) malloc(10*sizeof(int));
    p[0] =22;
    p[1] =33;
    return p;
}

int main()
{
    int *p = fun();
    //print here
    free(p);
    return 0;

}