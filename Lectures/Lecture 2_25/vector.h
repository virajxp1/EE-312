
#include <stdint.h>

#define STEP 10

typedef struct {
    int32_t size;
    int32_t len;
    int32_t *elems;
    int32_t id;
} Vector;

Vector* vecInit();

/*
 * Destroys the give vector and elements.
 */
void vecDestroy(Vector *vec);

/*
 * pre: vec should not be null
 * post: no state of the program is changed and return value is length
 * of the array.
 */
int32_t vecLen(Vector *vec);
int32_t vecSize(Vector *vec);
void vecAdd(Vector *const vec, int32_t const el);
void vecPrint(const Vector *const vec);
