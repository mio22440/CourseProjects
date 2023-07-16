#include<stdio.h>

int main(void)
{
	int m,n,a;
	
	printf("Enter two integers: ");
	scanf("%d %d",&m,&n);
	
	while(a != 0){
		a = m % n;
		m = n;
		n = a;
	}
	
	printf("Greatest common divisor: %d\n",m);
	
	return 0;
}
