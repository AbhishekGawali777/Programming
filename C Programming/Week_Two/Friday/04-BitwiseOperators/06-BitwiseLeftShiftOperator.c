#include <stdio.h>

void ABG_PrintBinaryFormOfNumber(unsigned int);

int main(void)
{
	unsigned int ABG_uiNum;
	unsigned int ABG_uiResult;
	unsigned int ABG_uiNumOfBits;

	printf("\n\n");
	printf("Enter An Integer :\t");
	scanf("%u", &ABG_uiNum);

	printf("\n\n");
	printf("Enter How Many Bits You Want To Shift  Given Number = %d To Right.?:\t", ABG_uiNum);
	scanf("%u", &ABG_uiNumOfBits);

	printf("\n\n\n\n");
	ABG_uiResult = ABG_uiNum << ABG_uiNumOfBits;
	printf("Bitwise LEFT_SHIFTing A = %d By %d Bits\nGives The Result (Decimal).\n\n", ABG_uiNum, ABG_uiNumOfBits, ABG_uiResult);

	ABG_PrintBinaryFormOfNumber(ABG_uiNum);
	ABG_PrintBinaryFormOfNumber(ABG_uiResult);

	return(0);
}

void ABG_PrintBinaryFormOfNumber(unsigned int ABG_uiFormalNumber)
{
	unsigned int ABG_uiNum;
	unsigned int ABG_uiQuotient;
	unsigned int ABG_uiRemainder;
	unsigned int ABG_uiLoopCounter;
	unsigned int ABG_uiBinaryArray[16];

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 16; ABG_uiLoopCounter++)
		ABG_uiBinaryArray[ABG_uiLoopCounter] = 0;

	printf("The Binary Form Of Decimal Integer %d Is :\t", ABG_uiFormalNumber);

	ABG_uiLoopCounter = 15;
	ABG_uiNum = ABG_uiFormalNumber;

	while (ABG_uiNum != 0)
	{
		ABG_uiQuotient = ABG_uiNum / 2;
		ABG_uiRemainder = ABG_uiNum % 2;
		ABG_uiBinaryArray[ABG_uiLoopCounter] = ABG_uiRemainder;
		ABG_uiNum = ABG_uiQuotient;
		ABG_uiLoopCounter--;
	}

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 16; ABG_uiLoopCounter++)
		printf("%d", ABG_uiBinaryArray[ABG_uiLoopCounter]);

	printf("\n\n");
}
