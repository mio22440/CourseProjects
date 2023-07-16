#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

unsigned int input16Hex();
unsigned int genCheck(int num, unsigned int *list);

int main(int argc, char **argv) {
	int blkNum;
	unsigned int *blkList;
	scanf("%d", &blkNum);
	blkList = (unsigned int*)calloc(blkNum, sizeof(int));
	
	int i;
	for (i = 0; i < blkNum; i++)
		blkList[i] = input16Hex();

	unsigned int checkSum;
	checkSum = genCheck(blkNum, blkList);

	printf("%04x\n", checkSum);

	return 0;
}

unsigned int input16Hex() {
	unsigned int temp = 0, hex = 0;
	char inputChar;

	do {
		temp = getchar();
	} while (temp == 10);
	
	while (temp != 10) {
		if (48 <= temp && temp <= 57)
			temp -= '0';
		else if (97 <= temp && temp <= 102)
			temp -= ('a'-10);
		else if (65 <= temp && temp <= 70)
			temp -= ('A'-10);
		else {
			printf("--illegal format--");
			return -1;
		}

		hex <<= 4;
		hex |= temp;
		
		temp = getchar();
	}
	
	return hex;
}

unsigned int genCheck(int num, unsigned int *list) {
	int checkSum = 0;

	int i;
	for (i = 0; i < num; i++) {
		checkSum += list[i];
		while(checkSum & 0x10000) {
			checkSum &= 0xffff;
			checkSum += 1;
		}	
	}

	checkSum = (~checkSum) & 0xffff;

	return checkSum;
}