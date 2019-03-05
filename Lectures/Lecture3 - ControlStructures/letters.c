
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

int main(void) {
    int32_t upper_case = 0;
    int32_t lower_case = 0;
    int32_t digits = 0;
    char c;
    while(1) {
        while ((c = getchar()) != '\n') {
            if (isupper(c)) {
                upper_case++;
            }
            if (islower(c)) {
                lower_case++;
            }
            if (isdigit(c)) {
                digits++;
            }
        }
        printf("%d %d %d\n", upper_case, lower_case, digits);
        upper_case=0;
        lower_case=0;
        digits=0;
    }


    return 0;
}
