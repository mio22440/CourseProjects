#include<stdio.h>

int main(void)
{
	int a,b,i,c,d=1;
	
	printf("Enter number of days in month: ");
	scanf("%d",&a);
	printf("Enter starting day of the week (1=Sun, 7=Sat): ");
	scanf("%d",&b);
	
	printf("\n");

	
	for(c = 1;c < b;c++){
        if(c == b-1){
            printf("%c",' ');
            printf("%c",' ');
            break;
        }
			printf("%c",' ');
			printf("%c",' ');
			printf("%c",' ');
	}
		
	
	for(i = 1;i <= a;i++){
		
	
        if(i>=1&&i<=9){
        	printf("%c",' ');
        } 
        if(i!=7+1-b+1&&i!=14+1-b+1&&i!=21+1-b+1&&i!=28+1-b+1&&i!=35+1-b+1){
        	if(b!=1||i!=b){
    	        printf(" ");
	        }

         }
	    printf("%d",i);
       // printf("%c",' ');
        
        
        if(i==7+1-b||i==14+1-b||i==21+1-b||i==28+1-b||i==35+1-b){
    	      printf("\n");
    	      }
        if(i == a&&i!=7+1-b&&i!=14+1-b&&i!=21+1-b&&i!=28+1-b&&i!=35+1-b){
        	 printf("\n");
        }

	}

	return 0;
}
  