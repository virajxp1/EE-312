#include <stdio.h>
#include <stdint.h>

#define LEN 50

double dot(double *a, double *b, int len) {
    double s = 0;
    for (int32_t i = 0; i < len; i++) {
        s += a[i] * b[i];
    }
    return s;
}

int main() {
    double a[LEN];
    double b[LEN];
    int32_t len;

    while (1) {
        /* Read length */
        printf("enter the length: ");
        scanf("%d", &len);

        /* Check if length is valid */
        if (len <= 0 || len > LEN) {
            break;
        }

        /* Read elements for the first array */
        printf("enter the elements for the first array: ");
        for (int32_t i = 0; i < len; i++) {
            scanf("%lf", &a[i]);
        }

        /* Read elements for the second array */
        printf("enter the elements for the second array: ");
        for (int32_t i = 0; i < len; i++) {
            scanf("%lf", &b[i]);
        }

        /* Compute the dot product */
        double s = dot(a, b, len);
        printf("dot product is %g\n", s);
    }

    return 0;
}
