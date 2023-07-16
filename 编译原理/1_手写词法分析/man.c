#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h>//to use the func "strcmp"

int charClass;
#define MAX_LEN 100
char lexeme[MAX_LEN];
char nextChar;
char next2Char;
int lexLen;
int token;
int nextToken;
FILE *inFile;

#define LETTER 0
#define DIGIT 1
#define UNKOWN 999

enum {
	ONE = 258, OF,
	ABSTRACT,   CONTINUE,   FOR,          NEW,         SWITCH,
	ASSERT,     DEFAULT,    IF,           PACKAGE,     SYNCHRONIZED,
	BOOLEAN,    DO,         GOTO,         PRIVATE,     THIS,
	BREAK,      DOUBLE,     IMPLEMENTS,   PROTECTED,   THROW,
	BYTE,       ELSE,       IMPORT,       PUBLIC,      THROWS,
	CASE,       ENUM,       INSTANCEOF,   RETURN,      TRANSIENT,
	CATCH,      EXTENDS,    INT,          SHORT,       TRY,
	CHAR,       FINAL,      INTERFACE,    STATIC,      VOID,
	CLASS,      FINALLY,    LONG,         STRICTFP,    VOLATILE,
	CONST,      FLOAT,      NATIVE,       SUPER,       WHILE,/* GOTO, CONST,*/ 
	
	ID,			EQU,			GEQU,		LEQU,		
	CONSTSTRING,	INTEGER,		FLOA_POINT,		ERROR};/*WHILE = 258, IF, ELSE, FOR, RET, INT, ID, EQU, GEQU, LEQU, ERROR };*/

const char *keywords[] = { "one" "of"
"abstract","   continue","   for","          new","         switch","\
assert","     default","    if","           package","     synchronized","\
boolean","    do","         goto","         private","     this","\
break","      double","     implements","   protected","   throw","\
byte","       else","       import","       public","      throws","\
case","       enum","       instanceof","   return","      transient","\
catch","      extends","    int","          short","       try","\
char","       final","      interface","    static","      void","\
class","      finally","    long","         strictfp","    volatile","\
const","      float","      native","       super","       while", /*"goto", "const",*/ };/*"while", "if", "else", "for", "return", 0 };*//*Here is a little difference from the book
																because we can not use const char* to initialize
							
							the char**/

//函数声明
void addChar();//将nextChar存入lexeme数组
void getChar();//从文件读取两个字符并存入next1Char和next2Char,并且把next1Char的类型存入charClass中
void getNonBlank();
int checkSymbol(char ch, char nextCh);
void checkKeywords(char *pword);
int lexer();


//函数实现
void addChar(){
	if (lexLen <= MAX_LEN - 2) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else {
		printf("ERROR:lexeme is too long. \n");
	}
}

void getChar() {
	static int firstRun = 1;
	if (firstRun) {
		nextChar = getc(inFile);
		next2Char = getc(inFile);
		firstRun = 0;
	}
	else {
		nextChar = next2Char;
		next2Char = getc(inFile);
	}

	if (nextChar == EOF) {
		charClass = EOF;
	}
	else {
		if (isalpha(nextChar) || nextChar == '_') {
			charClass = LETTER;
		}
		else if (isdigit(nextChar)) {//it will throw error if there is no "{"
			charClass = DIGIT;
		}
		else {
			charClass = UNKOWN;
		}
	}
}

void getNonBlank() {
	while (isspace(nextChar)) {
		getChar();
	}
}

int checkSymbol(char ch, char nextCh) {
	switch (ch) {
	case'(':case')':case';':case'+':case'-':case'.'://20191013add case'.'
		addChar();
		nextToken = ch;
		break;
	case'=':
		addChar();
		nextToken = ch;
		if (nextCh == '=') {
			getChar();
			addChar();
			nextToken = EQU;
		}
		break;
	case'>':
		addChar();
		nextToken = ch;
		if (nextCh == '=') {
			getChar();
			addChar();
			nextToken = GEQU;
		}
		break;
	case'<':
		addChar();
		nextToken = ch;
		if (nextCh == '=') {
			getChar();
			addChar();
			nextToken = LEQU;
		}
		break;
	case EOF:
		addChar();
		nextToken = EOF;
	default:
		printf("ERROR:unkown character'%c'. \n",ch);
		nextToken = ERROR;
	}
	return nextToken;
}

void checkKeywords(char *pword) {
	int i = 0;
	while (keywords[i] != 0) {
		const char *pkeyword = keywords[i];//so there is also an extra "const"
		if (strcmp(pword, pkeyword) == 0) {
			nextToken = 258 + i;
			return;
		}
		i++;
	}
}

int lexer() {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {
	case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT || nextChar == '_') {
				addChar();
				getChar();
			}
			nextToken = ID;

			//check if the current id is a keyword
			checkKeywords(lexeme);
			break;
	case DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT) {
			addChar();
			getChar();
		}
		if (nextChar == '.') {
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = FLOA_POINT;
			break;
		}
		nextToken = INT;
		break;

	case UNKOWN:
		if (nextChar == '"') {
			addChar();
			while (nextChar != '"') {
				getChar();
				addChar();
			}
			addChar();
			getChar();
			nextToken = CONSTSTRING;
			break;
		}
		else {
			checkSymbol(nextChar, next2Char);
			getChar();
			break;
		}
		
	case EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;
	}

	printf("<%6d,   %s   >\n", nextToken, lexeme);
	return nextToken;
}

void main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("ERROR:input file name is needed. \n");
		exit(0);
	}
	inFile = fopen(argv[1], "r");
	if (inFile == NULL) {
		printf("ERROR:can not open file. \n");
		exit(0);
	}
	getChar();
	while (nextToken != EOF) {
		lexer();
	}

	return;
}
