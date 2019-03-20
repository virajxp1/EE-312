
/* Set <Project5.cpp>
 * EE 312 Project 5 submission by
 * Viraj Parikh
 * VHP286
 * Slip days used: <0>
 * Spring 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */


/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}
/* done for you already */
void displaySet(const Set* self) {
	int k;

	printf("{");

	if (self->len == 0) {
		printf("}");
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* return true if x is an element of self */
// normal binary search
bool isMemberSet(const Set* self, int x) {
    //log(n) = binary search
    int min = 0;
    int max = (self->len)-1;
    while (min <= max) {
    	int mid = (max + (min)) / 2;
    	if (self->elements[mid] < x)
    		min = mid +1;
    	else if (self->elements[mid] > x)
    		max = mid-1;
    	else
    		return true;
        }
    return false;
}

/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */

void insertSet(Set* self, int x) {
    if(self->elements == nullptr) {
        createSingletonSet(self,x);
    }
	else if(!isMemberSet(self,x)) {
		int i;
		self->len++;
		self->elements = (int*)realloc(self->elements, sizeof(int)*self->len); //add extra space
		for(i = self->len-2 ;(i>=0 && x<self->elements[i]);i--) {
			self->elements[i+1] = self ->elements[i];  // start at back and go until x<element 
		}
		self->elements[i+1] = x; //insert into the element where x no greater than previous element 
	}
}

/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */

void removeSet(Set* self, int x) {
    if(isMemberSet(self,x)) {
        int i =0;
        for(;i<self->len;i++) {
            if(x<self->elements[i]) {
                self->elements[i-1]=self->elements[i]; //shift all elements greater than x by one and replace 
            }
        }
        self->len--;
    }

}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if (self->len == other->len) {
        for(int i =0; i<self->len;i++) {
            if(self->elements[i] != other->elements[i]) //all elements are equall 
                return false;
        }
        return true;
    }
	return false;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if(self->elements == nullptr) {
        return true;
    }
    /*if(isEqualToSet(self,other))
    	return true;*/
    int i =0; int j = 0;
    // i = bigger set j = smaller set
	while(i<self->len && j<other->len) {
		if(self->elements[i] == other->elements[j]) {
			i++;
			j++;
		}
		else if(self->elements[i] < other->elements[j]) {
			return false; // this signifies that self is not in other so returns false 
		}
		else {
			i++; //self x can only be equall orgreater than x
		}
	}

	return (i == self->len);
}

/* remove all elements from self that are not also elements of other */
//use fact that its sorted!
void intersectFromSet(Set* self, const Set* other) {
    int i =0;
    int j =0;
	int buffer_l = self->len + other->len;
	int buffer[buffer_l];
	int k =0;
    Set new_set;
    createEmptySet(&new_set);
	while(i<self->len && j<other->len) {
		if(self->elements[i] == other->elements[j]) { //insert only if the element is in both sets
			buffer[k] = self->elements[i];
			k++;
			i++; //increment both ptrs
			j++;
		}
		else if(self->elements[i] < other->elements[j])  
			i++;
		else
			j++;
	}
	buffer_l =k;
	k=0;
	new_set.len	= buffer_l;
	new_set.elements = (int*) (malloc(buffer_l * sizeof(int)));
	for(k=0;k<new_set.len;k++) {
		new_set.elements[k] = buffer[k]; //copy over buffer into new set
	}
    assignSet(self,&new_set);
    destroySet(&new_set);
}

/* remove all elements from self that are also elements of other */
//use fact that its sorted!
void subtractFromSet(Set* self, const Set* other) {
	int i =0;
	int j =0;
	int buffer_l = self->len + other->len;
	int buffer[buffer_l];
	int k =0;
	Set new_set;
	createEmptySet(&new_set);
	while(i<self->len && j<other->len) {
		if(self->elements[i] == other->elements[j]) {
			i++;
			j++;
		}
		else if(self->elements[i] < other->elements[j]) {
			buffer[k] = self->elements[i]; //insert if not in other set 
			k++;
			i++;
		}
		else
			j++;
	}
	while(i<self->len) {
		buffer[k] = self->elements[i];
		k++;
		i++;
	}
	buffer_l =k;
	k=0;
	new_set.len	= buffer_l;
	new_set.elements = (int*) (malloc(buffer_l * sizeof(int)));

	for(k=0;k<new_set.len;k++) {
		new_set.elements[k] = buffer[k]; //copy over remaining elements of self
	}
    assignSet(self,&new_set);
    destroySet(&new_set);
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
//use fact that its sorted!
//elemenets of both go into array just no duplicates!
void unionInSet(Set* self, const Set* other) {
	int i =0;
	int j =0;
	int buffer_l = self->len + other->len;
	int k =0;
	Set new_set;
	createEmptySet(&new_set);
	new_set.elements = (int*) malloc(buffer_l * sizeof(int));
	while(i<self->len && j<other->len) {
		if(self->elements[i] == other->elements[j]) {
			new_set.elements[k] = self->elements[i];
			k++;
			i++;
			j++;
		}
		else if(self->elements[i] < other->elements[j]) {
			new_set.elements[k] = self->elements[i];
			k++;
			i++;
		}
		else {
			new_set.elements[k] = other->elements[j];
			k++;
			j++;
		}
	}
	while(j<other->len) {
		new_set.elements[k] = other->elements[j];
		k++;
		j++;
	}
	while(i<self->len) {
		new_set.elements[k] = self->elements[i];
		k++;
		i++;
	}

	new_set.len = k;
	assignSet(self,&new_set);
	destroySet(&new_set);
}
