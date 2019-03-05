#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "vector.h"



Vector* vecInit() {
    static int32_t uid = 0;
    Vector *vec = malloc(sizeof(Vector));
    vec->size = STEP;
    vec->len = 0;
    vec->elems = malloc(sizeof(int32_t) * vec->size);
    vec->id = uid;
    uid++;
    return vec;
}

void vecDestroy(Vector *vec) {
    free(vec->elems);
    free(vec);
}

int32_t vecLen(Vector *vec) {
    return vec->len;
}

int32_t vecSize(Vector *vec) {
    return vec->size;
}

void vecAdd(Vector *const vec, const int32_t el) {
    if (vec->len == vec->size) {
        vec->size += STEP;
        vec->elems = realloc(vec->elems, sizeof(int32_t) * vec->size);
    }
    vec->elems[vec->len] = el;
    vec->len++;
}

void vecPrint(const Vector *const vec) {
    printf("Vector len=%d, size=%d\n", vec->len, vec->size);
    for (int32_t i = 0; i < vec->len; i++) {
        printf("%d ", vec->elems[i]);
    }
    printf("\n");
}

Vector* vecSearch(Vector *vec, int8_t (*cond)(int32_t)) {
    Vector *res =vecInit();
    for(int i=0; i<vec->len;i++) {
        if(cond(vec->elems[i])) {
            vecAdd(res, vec->elems[i]);
        }
    }
    return res;

}

int8_t lt10(int32_t val) {
    return val<10;
}

int main(void) {
    Vector *vec = vecInit();
    for(int i=0; i<10;i++)
    {
        vecAdd(vec,rand()%10 +1);
    }
    vecPrint(vec);

    Vector *res = vecSearch(vec,&lt10);
    vecPrint(res);
    

    vecDestroy(vec);
    vecDestroy(res);

}

//Prefix variabes with const so the values cannot be changed in the function 
//Optimize execution because knows that value is not going to change 
//not limited to primitive types
//const Vector *const vec makes everything in vector read only
//Signatures should match in implementation 
//STATIC -> allocated once before at the begining of the program 
//like a global variable 
//can only be accessed in the function in which its declared
//allocated in data 
//Static declared as a global variable -> only accessible in the current file 
//Functions in header should be written as Static 
//Function pointer -> the argument to our function is a function 
//Check a certain condition 
//by passing a different function in each argument can check multiple function



