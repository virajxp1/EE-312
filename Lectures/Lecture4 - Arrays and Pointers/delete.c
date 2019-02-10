#include <stdio.h>
#include <stdlib.h>


void delete(int* a,int len,int i) {
	while (i<len)
	{
		a[i]=a[i+1];
		i++;
	} 
	

}

void check(int* a,int val,int len) {	
	for (int i=0;i<len;i++) {
		if (a[i]==val){
			//printf("%d",*a+i);
			delete(a,len,i);
		}
	}
}


int main() {
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int val;
	int* pa=a;
	printf("enter val");
	scanf("%d",&val);
	check(pa,val,10);
	for (int i=0;i<9;i++){
		printf("%d",a[i]);
	}







}

