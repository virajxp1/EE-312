/*
 * Set ADT
 * Project5.c 
 *
 * My Name
 * My Section Time
 * Spring 2017
 *
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


bool linearSearch(const Set* self, int key) {
	for(int i = 0;i<self->len;i++) {
		if(self->elements[i] == key)
			return true;
	}
	return false;
}

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
				int x = self->elements[k];
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


//----------------------------------------------
/*
 *
 * is member set done
 * insert done
 * remove done
 * is equall to done
 * is subset of done
 *
 *
 * to do
 *
 * union
 * intersection
 * subtraction
 */

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    //log(n) = binary search
    int min = 0;
    int max = (self->len)-1;
    while (min <= max) {
    	int mid = (max + (min)) / 2;
    	int el = self->elements[mid];
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
		self->len++;
		self->elements = (int*)realloc(self->elements, sizeof(int)*self->len);
		self->elements[self->len-1] = 0;
		int i = self->len-1;
		for(;(i>=0 && x<self->elements[i]);i--) {
			self->elements[i+1] = self ->elements[i];
		}
		self->elements[i] = x;
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
    if(!isMemberSet(self,x)) {
        int i =0;
        for(;i<self->len;i++) {
            if(x>=self->elements[i]) {
                self->elements[i]=self->elements[i+1];
            }
        }
    }
}


/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if (isEmptySet(self) && isEmptySet(other))
        return true;
    if (self->len == other->len) {
        int i = 0;
        int j = 0;
        // i = bigger set j = smaller set
        while (j < other->len) {
            if (other->elements[j] == self->elements[i]) {
                j=0;
                i++;
                if (i == self->len)
                    return true;
            }
            else
                j++;
        }
    }
	return false;
}
/* return true if every element of self is also an element of other */
// increment untill u find in small set then increment big set
//keep self still and if any element of other matches self then increase pointer of both
// arrays
//else increase other and set b to 0
//return true if the array b is completly traveresed
//return false when the big array runs out
bool isSubsetOf(const Set* self, const Set* other) {
    if(self->elements == nullptr) {
        return true;
    }
    int i =0; int j = 0;
    // i = bigger set j = smaller set
	while(j<other->len) {
		if(other->elements[j] == self->elements[i]) {
			j=0;
			i++;
			if(i == self->len)
				return true;
		}
		else {
			j++;
		}
	}
	return false;
}



/* remove all elements from self that are not also elements of other */
// loop through both list if they equall one add one and increment both values
void intersectFromSet(Set* self, const Set* other) {
    int i =0;
    int j =0;
    Set new_set;
    createEmptySet(&new_set);

   while(i<self->len) {
       if(other->elements[i] == self->elements[j]) {
           insertSet(&new_set,other->elements[i]);
           j=0;
           i++;
       }
       else {
           j++;
           if(j==self->len) {
               j=0;
               i++;
           }
       }
   }
   assignSet(self,&new_set);

}
//loop self . for each el if not in other

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
	for(int i = 0;i<self->len;i++) {
		if(linearSearch(other,self->elements[i])) {
			removeSet(self,self->elements[i]);
		}
	}
	//loop for each el in self if in other remove
}

/* add all elements of other to self (obviously, without creating duplicate elements) */



void unionInSet(Set* self, const Set* other) {
	int i =0;
	int j =0;

	while(i<other->len) {
		if(other->elements[i] != self->elements[j]) {
			j++;
			if(j == self->len) {
				j = 0;
				insertSet(self,other->elements[i]);
				i++;
			}
		}
		else {
            j = 0;
            i++;
        }

	}
}


