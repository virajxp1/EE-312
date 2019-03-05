 #include <stdio.h>
 #include <stdlib.h>
/* Write a program that finds a min value in an array of floating
 * point numbers. Repeat the program until the length of the
 * array is an incorrect value.
 */
int min(int* a, int l) {
	int m = a[0];
	for(int i=1;i<l;i++) {
		if (a[i]<m) {
			m=a[i];
		}
	}

	return m;
}

int main () { 
	int a[10];
	int Len;
	int* pa=a;
	while(1) {
		printf("Enter Length: \n"); 
		scanf("%d",&Len);
		if(Len<=0 || Len>10)
			break;
		printf("Enter array: \n");
		for(int i=0;i<Len;i++) 
			scanf("%d",pa+i);
		printf("\n");
		printf("%d\n",min(pa,Len));

	}

	



}
