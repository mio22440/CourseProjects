#include<stdio.h>

int main(void)
{
	int a[10]={0};
	int b,i;
	long c;
	
	printf("Enter a number: ");
	scanf("%ld",&c);
	
	if(c==0){
		a[0]++;// 
	}
	
	while(c>0){
	    b = c % 10;
		
        a[b] += 1;
		
       c = c / 10;
	}
	
	printf("Digit:\t\t");
	for(i=0;i<10;i++){
		printf("%d",i);
		if(i!=9){
			printf("  ");
		}
	}
	printf("\n");

    printf("Occurrences:\t");
    for(i=0;i<10;i++){
    	printf("%d",a[i]);
    	if(i!=9){
	    	printf("  ");
	    }
    }
    printf("\n");
	 
	 return 0;
}
