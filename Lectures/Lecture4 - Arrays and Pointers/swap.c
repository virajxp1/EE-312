
#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int main(void) {
    int a = 33;
    int b = 44;
    swap(&a, &b);
    printf("%d %d\n", a, b);

    int array[10] = {1, 2, 3, 4, 5, 6};
    double darray[10] = {1.2};

    double *dp = darray;
    dp++;
    // dp == &darray[1];

    int *p = &array[0];
    int **p = &p;

    int *q = &array[1]; // p + 1

    p[0] = 22;
    p = p + 1;
    p++;
    //    printf("%d %d %d %d\n", p[0], array[0], 0[p], 0[array]);
    printf("%d, %d\n", *p, p[100]);

    return 0;
}
