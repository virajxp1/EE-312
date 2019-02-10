
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t g = 55;

int32_t mul(int32_t a, int32_t b) {
    return a * b;
}

int32_t divi (int32_t a, int32_t b) {
	return a / b;
}


int32_t max(int32_t array[], int len) {
    int32_t max = array[0];
    int32_t i = 1;
    while (i < len) {
        if (max < array[i]) {
            max = array[i];
        }
        i++;
    }
    return max;
}

int32_t min(int32_t array[],int len){
	int32_t min = array[0];
	int32_t i;
	for (i = 1;i < len;i++) {
		if (array[i]<min) {
			min=array[i];
		}
	}
	return min;
}

int main(void) {
    int32_t i;
    int a,b;
    int32_t n[4] = {1, 2, 34, 5};
    int32_t length = divi(sizeof(n),sizeof(int32_t));


    printf("the array has %d elements\n",length);
    printf("the min value is %d",min(n,length));

   for(i=1; i<length; i++)
   {
   	if (n[i]<n[i-1]){
   		int j = rand();
   		n[i-1]=n[i];
   		n[i]=j;

   	}
   }
    for(i=0;i<length;i++){
    	printf("\n %d ",n[i]);

    }
 	return 0;
 }


