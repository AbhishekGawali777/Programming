#include <stdio.h>

int main(void)
{
	int ABG_MyStrlen(char[]);

	char ABG_strArray[10][15] = { "Hello", "Welcome", "To" ,"Real", "Time" , "Rendering", "Batch", "(2020-2021)",
								  "Of", "ASTROMEDICOMP!" };

	int ABG_iArraySize;
	int ABG_iNumberOfRows;
	int ABG_iLoopCounter1;
	int ABG_iLoopCounter2;
	int ABG_iStrLengthArray[10];

	ABG_iArraySize = sizeof(ABG_strArray);
	ABG_iNumberOfRows = sizeof(ABG_strArray) / sizeof(ABG_strArray[0]);

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumberOfRows; ABG_iLoopCounter1++)
	{
		ABG_iStrLengthArray[ABG_iLoopCounter1] = ABG_MyStrlen(ABG_strArray[ABG_iLoopCounter1]);
	}

	printf("\n\n");
	printf("Strings In 2D Array : \n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumberOfRows; ABG_iLoopCounter1++)
	{
		printf("\nString Number %d => %s\n\n", (ABG_iLoopCounter1 + 1), ABG_strArray[ABG_iLoopCounter1]);
		
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_iStrLengthArray[ABG_iLoopCounter1]; ABG_iLoopCounter2++)
		{
			printf("Character %d = %c\n", ABG_iLoopCounter2, ABG_strArray[ABG_iLoopCounter1][ABG_iLoopCounter2]);
		}
	}

	return(0);
}

int ABG_MyStrlen(char strArrayFormal[])
{
	int ABG_iStringLength = 0;
	int ABG_iLoopCounter;

	for (ABG_iLoopCounter = 0; strArrayFormal[ABG_iLoopCounter] != '\0'; ABG_iLoopCounter++)
	{
		ABG_iStringLength++;
	}

	return (ABG_iStringLength);
}