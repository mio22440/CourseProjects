#include<stdio.h>

int main(void)
{
	int a,b,c;
	
	b = 2;
	
	printf("Enter a number: ");
	scanf("%d",&a);
	
	
	
	do{
		c = b * b;
		
		if(c<=a)printf("%d\n",c);
		
		b = b + 2;
	}while(c < a);
	
	 return 0;
}
