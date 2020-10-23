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

	ABG_strArray[0][0] = 'M';
	ABG_strArray[0][1] = 'y';
	ABG_strArray[0][2] = '\0';

	ABG_strArray[1][0] = 'N';
	ABG_strArray[1][1] = 'a';
	ABG_strArray[1][2] = 'm';
	ABG_strArray[1][3] = 'e';
	ABG_strArray[1][4] = '\0';

	ABG_strArray[2][0] = 'I';
	ABG_strArray[2][1] = 's';
	ABG_strArray[2][2] = '\0';

	ABG_strArray[3][0] = 'A';
	ABG_strArray[3][1] = 'b';
	ABG_strArray[3][2] = 'h';
	ABG_strArray[3][3] = 'i';
	ABG_strArray[3][4] = 's';
	ABG_strArray[3][5] = 'h';
	ABG_strArray[3][6] = 'e';
	ABG_strArray[3][7] = 'k';
	ABG_strArray[3][8] = '\0';

	ABG_strArray[4][0] = 'G';
	ABG_strArray[4][1] = 'a';
	ABG_strArray[4][2] = 'w';
	ABG_strArray[4][3] = 'a';
	ABG_strArray[4][4] = 'l';
	ABG_strArray[4][5] = 'i';
	ABG_strArray[4][6] = '.';
	ABG_strArray[4][7] = '\0';

	printf("\n\n");
	printf("The String in The 2D Character Array Are : \n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_iNumberOfRows; ABG_iLoopCounter++)
	{
		printf("%s ", ABG_strArray[ABG_iLoopCounter]);
	}

	printf("\n\n");

	return(0);
}