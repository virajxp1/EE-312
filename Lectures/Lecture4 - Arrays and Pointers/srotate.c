#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LEN 100

int main() {
    char a[LEN];
    char b[LEN];

    /* load string 1 */
    char *pa = a;
    while ((*pa = getchar()) != '\n') {
        pa++;
    }
    *pa = '\0';

    /* load string 2 */
    char *pb = b;
    while ((*pb = getchar()) != '\n') {
        pb++;
    }
    *pb = '\0';

    /* print strings to check if correct */
    printf("%s and %s\n", a, b);

    /* append */
    pb = b;
    while (*pb) {
        *pa = *pb;
        pa++;
        pb++;
    }
    *pa = '\0';

    /* rotate */
    for (pa = a, pb = a + strlen(a) - 1; pa < pb; pa++, pb--) {
        char tmp = *pa;
        *pa = *pb;
        *pb = tmp;
    }

    /* print the result */
    printf("%s\n", a);

    return 0;
}
