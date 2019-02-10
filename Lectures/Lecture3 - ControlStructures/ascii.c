
#include <stdio.h>
#include <stdint.h>

int main() {
    printf("\n");
    int32_t counter=0;
    for (char c = ' '; c <= '~'; c++) 
    {
        printf("%3d %3c %3x ",c,c,c);
        counter++;
        if(counter == 5)
        {
            printf("\n");
            counter =0;
        }
    }

    return 0;
}
