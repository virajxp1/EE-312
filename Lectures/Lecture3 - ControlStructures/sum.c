
#include <stdint.h>
#include <stdio.h>

int main(void) {
    int32_t sum = 0;
    int32_t factorial;
    int32_t n=5;

    //scanf("%d", &n);

    for (int32_t i = 1; i <= n; i++)
    {
    	factorial =1;
        for(int32_t j=1;j<=i;j++)
        {
			factorial *= j;
        }

		sum += factorial;
    }

    printf("sum = %d\n", sum);

    return 0;
}
