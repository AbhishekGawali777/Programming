#include <stdio.h>

int main(void)
{
	void ABG_MyStrCpy(char[], char[]);

	char ABG_strArray[5][10];

	int ABG_CharSize;
	int ABG_iArraySize;
	int ABG_iLoopCounter;
	int ABG_iNumberOfRows;
	int ABG_iNumberOfCols;
	int ABG_iNumberOfElements;
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

	printf("\n\n");
	printf("Strings In 2D Array Are : \n\n");

	ABG_MyStrCpy(ABG_strArray[0], "My");
	ABG_MyStrCpy(ABG_strArray[1], "Name");
	ABG_MyStrCpy(ABG_strArray[2], "Is");
	ABG_MyStrCpy(ABG_strArray[3], "Abhishek");
	ABG_MyStrCpy(ABG_strArray[4], "Gawali.");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_iNumberOfRows; ABG_iLoopCounter++)
	{
		printf("%s ", ABG_strArray[ABG_iLoopCounter]);
	}

	printf("\n\n");

	return(0);
}

void ABG_MyStrCpy(char* strDestinition, char* strSource)
{
	while (*strSource != '\0')
	{
		*strDestinition++ = *strSource++;
	}

	*strDestinition = '\0';
}