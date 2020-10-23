#include <stdio.h>

int main(int argc, char* argv[])
{
	// Function Prototype

	void ABG_PrintBinaryFormOfNumber(unsigned int);

	unsigned int ABG_uiNum1;
	unsigned int ABG_uiNum2;
	unsigned int ABG_uiResult;

	printf("\n\n");
	printf("Enter An Integer : \t");
	scanf("%d", &ABG_uiNum1);
	
	printf("\n\n");
	printf("Enter An Another Integer : \t");
	scanf("%d", &ABG_uiNum2);

	printf("\n\n\n");
	ABG_uiResult = ABG_uiNum1 & ABG_uiNum2;
	printf("Bitwise AND-ing of \nFirst Number = %d (Decimal) And Second Number = %d (Decimal) gives Result %d (Decimal).\n\n", ABG_uiNum1, ABG_uiNum2, ABG_uiResult);

	ABG_PrintBinaryFormOfNumber(ABG_uiNum1);
	ABG_PrintBinaryFormOfNumber(ABG_uiNum2);
	ABG_PrintBinaryFormOfNumber(ABG_uiResult);

	return(0);
}

void ABG_PrintBinaryFormOfNumber(unsigned int ABG_uiFormalNumber)
{
	unsigned int ABG_uiQuotient, ABG_uiRemainder;
	unsigned int ABG_uiNumber;
	unsigned int ABG_uiBinaryArray[8];
	unsigned int ABG_uiLoopCounter;

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