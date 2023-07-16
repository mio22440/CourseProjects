#include<stdio.h>

int main(void)
{
    float a,b,c,d,e,f,g;
    
	printf("Enter amount of loan: ");
	scanf("%f",&a);
	
	printf("Enter interest rate: ");
	scanf("%f",&b);
	
	printf("Enter monthly payment: \n");
	scanf("%f",&c);
	
	d = a * (1+b / 1200)-c;
	e = d * (1+b / 1200)-c;
	f = e * (1+b / 1200)-c;
	
	printf("Balance remaining after first payment: $%.2f\n",d);
	printf("Balance remaining after second payment: $%.2f\n",e);
	printf("Balance remaining after third payment: $%.2f\n",f);
	
	return 0;
}
