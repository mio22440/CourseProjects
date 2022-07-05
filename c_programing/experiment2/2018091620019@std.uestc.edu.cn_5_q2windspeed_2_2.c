#include<stdio.h>

int main(void)
{
	int a;
	
	printf("Enter a wind speed: "); 
	scanf("%d",&a);
	
	if(a<1)
	  printf("Calm\n");
	
	else if(a>=1&&a<=3)
	  printf("Light air\n");
	
	else if(a>=4&&a<=27)
	  printf("Breeze\n"); 
  	
    else if(a>=28&&a<=47)
	  printf("Gale\n"); 
  	
    else if(a>=48&&a<=63)
	  printf("Storm\n"); 
  	
    else
	  printf("Hurricane\n");     
	  
	return 0;  
	 
} 
