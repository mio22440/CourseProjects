#include<stdio.h>

int main(void)
{
	int a,b;
	
	printf("Enter a 24-hour time: ");
	scanf("%d:%d",&a,&b);
	
	if(a == 0){
		a = 12;
		printf("Equivalent 12-hour time: %d:%02d AM\n",a,b);
	}
	else if(a == 24||a == 12){
	    a = 12;
	    printf("Equivalent 12-hour time: %d:%02d PM\n",a,b);
	}
	else if(a > 0&&a < 12){
	    printf("Equivalent 12-hour time: %d:%02d AM\n",a,b);
	}
	else if(a > 12&&a <24){
		a = a - 12; 
		printf("Equivalent 12-hour time: %d:%02d PM\n",a,b);
	}
	else{
		printf("You entered an illegal time");
	}
	
	return 0;
}
