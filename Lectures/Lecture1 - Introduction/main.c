
#include <stdio.h>

/* -E                       Preprocess only; do not compile, assemble or link. */
/* -S                       Compile only; do not assemble or link. */
/* -c                       Compile and assemble, but do not link. */
/* -o <file>                Place the output into <file>. */

int main(void) {
    printf("hi Jon\n");

    int i = 1;
    while (i > 0) {
        i++;
    }

    printf("%d\n", i);

    return 0;
}
