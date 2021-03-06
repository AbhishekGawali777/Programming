#include <stdio.h>

void ABG_PrintBinaryFormOfNumber(unsigned int);

int main(int argc, char* argv[])
{
	unsigned int ABG_uiNum;
	unsigned int ABG_uiResult;

	printf("\n\n");
	printf("Enter Number :\t");
	scanf("%d", &ABG_uiNum);

	printf("\n\n\n\n");
	ABG_uiResult = ~ABG_uiNum;
	printf("Bitwise Ones Complement Of Number = %d Gives Result %d (Decimal).\n\n", ABG_uiNum, ABG_uiResult);

	ABG_PrintBinaryFormOfNumber(ABG_uiNum);
	ABG_PrintBinaryFormOfNumber(ABG_uiResult);

	return(0);
}

void ABG_PrintBinaryFormOfNumber(unsigned int ABG_uiFormalNumber)
{
	unsigned int ABG_uiNumber;
	unsigned int ABG_uiLoopCounter;
	unsigned int ABG_uiBinaryArray[8];
	unsigned int ABG_uiQuotient, ABG_uiRemainder;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 8; ABG_uiLoopCounter++)
		ABG_uiBinaryArray[ABG_uiLoopCounter] = 0;

	printf("Binary Form Of Decimal Integer %d Is \t=\t", ABG_uiFormalNumber);
	ABG_uiNumber = ABG_uiFormalNumber;

	ABG_uiLoopCounter = 7;

	while (ABG_uiNumber != 0)
	{
		ABG_uiQuotient = ABG_uiNumber / 2;
		ABG_uiRemainder = ABG_uiNumber % 2;
		ABG_uiBinaryArray[ABG_uiLoopCounter] = ABG_uiRemainder;
		ABG_uiNumber = ABG_uiQuotient;
		ABG_uiLoopCounter--;
	}

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 8; ABG_uiLoopCounter++)
		printf("%u", ABG_uiBinaryArray[ABG_uiLoopCounter]);

	printf("\n\n");
}