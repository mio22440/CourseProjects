#include<stdio.h>
#include<string.h>

#define MAX_LEN 20

int read_line(char str[], int n);//读入单词 

int main(void)
{
	char smallest_word[MAX_LEN+1]={'\0'}, largest_word[MAX_LEN+1]={'\0'};//用来存最大/最小单词 
	char input[MAX_LEN+1]={'\0'};//用来存输入的单词 
	char temp_word[MAX_LEN+1]={'\0'};//用来替换第一次最大最小单词，作为中间变量 
	int i=0;//控制第一次赋值给smallest_word，防止if的条件\0满足不了 
	//好像这样也不行... 
	
	while(1){
		printf("Enter word: ");
		read_line(input,20);
		
				
		if(strlen(input)==0)//为空时 
		   continue;

		if(i==0){
			strcpy(smallest_word,input);
		} 
		if(strcmp(input,smallest_word)<0){
			strcpy(smallest_word,input);
		}
		if(strcmp(input,largest_word)>0){
			strcpy(largest_word,input);
		}
		
		if(strcmp(smallest_word,largest_word)>0){
			strcpy(temp_word,largest_word);
			strcpy(largest_word,smallest_word);
			strcpy(smallest_word,temp_word);
		} 
		
		if(strlen(input)==4){
			break;
		}
		i++;
		
		if(strlen(input)==0)
		   break;

	} 
	
	printf("\n"); 
	
	printf("Smallest word: ");
	puts(smallest_word);
	
	printf("Largest word: ");
	puts(largest_word);
	
	return 0;
	
}




 int read_line(char str[], int n)
 {
 	int ch, i = 0;
 	
 	while((ch = getchar()) != '\n'){
	 	if(i < n){
	 		str[i++] = ch;
	 	}
	 }
    str[i] = '\0';
    return i;
 }
