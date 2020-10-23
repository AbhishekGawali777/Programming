#include <stdio.h>

int main(void)
{
	int ABG_MyStrlen(char[]);
	
	char ABG_strArray[10][15] = { "Hello", "Welcome", "To" ,"Real", "Time" , "Rendering", "Batch", "(2020-2021)",
								  "Of", "ASTROMEDICOMP!" };

	int ABG_CharSize;
	int ABG_iArraySize;
	int ABG_iLoopCounter;
	int ABG_iNumberOfRows;
	int ABG_iNumberOfCols;
	int ABG_iNumberOfElements;
	int ABG_ActualNumberOfChars = 0;

	printf("\n\n");
	
	ABG_CharSize = sizeof(char);

	ABG_iArraySize = sizeof(ABG_strArray);
	printf("Size Of Two Dimensional ( 2D ) Character Array Is = %d\n\n", ABG_iArraySize);


	ABG_iNumberOfRows = ABG_iArraySize / sizeof(ABG_strArray[0]);
	printf("\n\nNumber Of Rows In Two Dimensional (2D) Character Array Is : %d\n\n", ABG_iNumberOfRows);

	ABG_iNumberOfCols = sizeof(ABG_strArray[0]) / sizeof(ABG_strArray[0][0]); 
	// OR sizeof(ABG_strArray[0]) / ABG_CharSize;
	
	printf("\n\nNumber Of Columns In Two Dimensional (2D) Character Array Is : %d\n\n", ABG_iNumberOfCols);

	ABG_iNumberOfElements = ABG_iNumberOfRows * ABG_iNumberOfCols;
	printf("\n\nNumber Of Elements In Two Dimensional (2D) Character Array Is : %d\n\n", ABG_iNumberOfElements);


	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_iNumberOfRows; ABG_iLoopCounter++)
	{
		ABG_ActualNumberOfChars = ABG_ActualNumberOfChars + ABG_MyStrlen(ABG_strArray[ABG_iLoopCounter]);
	}
	
	printf("\n\n");
	printf("Strings In 2D Array Are : \n\n");

	printf("%s ", ABG_strArray[0]);
	printf("%s ", ABG_strArray[1]);
	printf("%s ", ABG_strArray[2]);
	printf("%s ", ABG_strArray[3]);
	printf("%s ", ABG_strArray[4]);
	printf("%s ", ABG_strArray[5]);
	printf("%s ", ABG_strArray[6]);
	printf("%s ", ABG_strArray[7]);
	printf("%s ", ABG_strArray[8]);
	printf("%s\n\n", ABG_strArray[9]);

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