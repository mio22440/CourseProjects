#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 10
#define COLS 10
int main(void)
{
	char ZimuArray[ROWS][COLS]={
	                             {'.','.','.','.','.','.','.','.','.','.'},
	                             {'.','.','.','.','.','.','.','.','.','.'},
								 {'.','.','.','.','.','.','.','.','.','.'},
								 {'.','.','.','.','.','.','.','.','.','.'},
								 {'.','.','.','.','.','.','.','.','.','.'},
	                             {'.','.','.','.','.','.','.','.','.','.'},
								 {'.','.','.','.','.','.','.','.','.','.'},
								 {'.','.','.','.','.','.','.','.','.','.'},
								 {'.','.','.','.','.','.','.','.','.','.'},
	                             {'.','.','.','.','.','.','.','.','.','.'}
								 };
	int Rows,Cols;
	int Direction;
	int Number;
	
	srand((unsigned) time(NULL));
	
	
	
	Rows = 0;
	Cols = 0;
	Number = 65;
	
	ZimuArray[Rows][Cols]= Number;//A
	do{
		do{//随机取得下一步的方向并保证不重复且不飞出去 
  	       Direction = rand() % 4;
	
	 
           if(Direction==0){
    	        if(Cols>0&&ZimuArray[Rows][Cols-1]=='.'){
	    	                 Cols -= 1;
	          }
           }
           else if(Direction==2){
   	             if(ZimuArray[Rows][Cols+1]=='.'){
       	   					 Cols += 1;
             	   }

           }
           else if(Direction==1){
           	     if
           	     (ZimuArray[Rows+1][Cols]=='.'){
        	    	         Rows += 1;
     	           }

           }
           else if(Direction==3){
    	      if(Rows>0&&ZimuArray[Rows-1][Cols]=='.'){
	    	   Rows -= 1;
              }
           }
           
           //当四个方向堵住时
		   if(Rows!=0&&Cols!=0&&
		   ZimuArray[Rows+1][Cols]!='.'&&
		   ZimuArray[Rows-1][Cols]!='.'&&
		   ZimuArray[Rows][Cols+1]!='.'&&
		   ZimuArray[Rows][Cols-1]!='.') {
   			break;
   		}
           
 
        }while(ZimuArray[Rows][Cols]!='.'/*||Rows<0||Cols<0*/);
        
    
	    Number += 1;
    
        ZimuArray[Rows][Cols] = Number;
        
        		   if(Rows!=0&&Cols!=0&&
		   ZimuArray[Rows+1][Cols]!='.'&&
		   ZimuArray[Rows-1][Cols]!='.'&&
		   ZimuArray[Rows][Cols+1]!='.'&&
		   ZimuArray[Rows][Cols-1]!='.') {
   			break;
   		}
   
	}while(Number<90);
    
    
    
    //输出数组 
    for(Rows=0;Rows<ROWS;Rows++){
		for(Cols=0;Cols<COLS;Cols++){
			printf(" %c ",ZimuArray[Rows][Cols]);
		}
		printf("\n");
	}
	
	printf("\n");
	
	return 0;
}
