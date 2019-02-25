// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Viraj Parikh
// VHP286
// Slip days used: <0>
// Spring 2019
// Copy and paste this file at the top of all your submitted source code files.

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "String.h"

#define SIGNATURE (~0xdeadbeef)

#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

bool isOurs(const UTString *s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/* 
 * Allocate a utstring on the heap. 
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */

//Problems : Capacity like how to know? null or 0s or crap data not really sure anything

UTString* utstrdup(const char* src) {
	UTString *ut_s = (UTString*)malloc(sizeof(UTString));
	ut_s->length = strlen(src);
	ut_s->capacity = ut_s->length;
	ut_s->string = (char*)malloc((ut_s->capacity+5)*sizeof(char));

	uint32_t i=0;
	for(i=0;i<=ut_s->length;i++)
		ut_s->string[i] = src[i];
	CHECK(ut_s) = SIGNATURE;
	return ut_s;
}

uint32_t utstrlen(const UTString* s) {
	assert(isOurs(s));
	return s->length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s. 
 * Update the length of s.
 * Return s with the above changes. */

UTString* utstrcat(UTString* s, const char* suffix) {
	assert(isOurs(s));
	int32_t i = s-> capacity - s->length;
	int32_t j = s-> length;
	int32_t k = 0;
	while(i>0&&suffix[k]!=0) {
		s->string[j]=suffix[k];
		i--;
		j++;
		k++;
	}
	s->length += k;
	s->string[s->length] = 0;
    CHECK(s) = SIGNATURE;
	return s;
}

/* 
 * Copy src into dst.
 *  dst must be a valid UTString. 
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst. 
 * Return dst with the above changes.
 */

UTString* utstrcpy(UTString* dst, const char* src) {
	assert(isOurs(dst));
	uint32_t i = 0;
    while(i<dst->capacity&&src[i]!=0) {
        dst->string[i]=src[i];
        i++;
    }
    dst->string[i]=0;
    dst->length =i;

    CHECK(dst) = SIGNATURE;
    return dst;
}

/*
 * Free all memory associated with the given UTString. 
 */

void utstrfree(UTString* self) {
	assert(isOurs(self));
    free(self->string);
	free(self);
}

/* 
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity, 
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata. 
 * Return s with the above changes.
 */


UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
	assert(isOurs(s));

    if(new_capacity <= s->capacity)
        return s;

    s->capacity = new_capacity;
    s->string = (char*)realloc(s->string,(new_capacity+5));
    return s;

}
