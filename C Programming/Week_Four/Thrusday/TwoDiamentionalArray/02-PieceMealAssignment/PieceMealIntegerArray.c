#include <stdio.h>

int main(void)
{
	int ABG_IntSize;
	int ABG_iArraySize;
	int ABG_iNumberOfRows;
	int ABG_iNumberOfCols;
	int ABG_iLoopCounter1;
	int ABG_iLoopCounter2;
	int ABG_iNumberOfElements;
	
	int ABG_iArray[3][5];

	ABG_IntSize = sizeof(int);

	ABG_iArraySize = sizeof(ABG_iArray);
	printf("\n\nSize Of Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iArraySize);

	ABG_iNumberOfRows = ABG_iArraySize / sizeof(ABG_iArray[0]);
	printf("\n\nNumber Of Rows In Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iNumberOfRows);

	ABG_iNumberOfCols = sizeof(ABG_iArray[0]) / sizeof(ABG_iArray[0][0]); // OR sizeof(ABG_iArray[0]) / ABG_IntSize;
	printf("\n\nNumber Of Columns In Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iNumberOfCols);

	ABG_iNumberOfElements = ABG_iNumberOfRows * ABG_iNumberOfCols;
	printf("\n\nNumber Of Elements In Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iNumberOfElements);

	printf("\n\n");
	printf("Elements In 2D Array Are : \n\n");

	ABG_iArray[0][0] = 10;
	ABG_iArray[0][1] = 20;
	ABG_iArray[0][2] = 30;
	ABG_iArray[0][3] = 40;
	ABG_iArray[0][4] = 50;

	ABG_iArray[1][0] = 12;
	ABG_iArray[1][1] = 67;
	ABG_iArray[1][2] = 84;
	ABG_iArray[1][3] = 91;
	ABG_iArray[1][4] = 89;


	ABG_iArray[2][0] = 46;
	ABG_iArray[2][1] = 58;
	ABG_iArray[2][2] = 24;
	ABG_iArray[2][3] = 34;
	ABG_iArray[2][4] = 78;

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumberOfRows; ABG_iLoopCounter1++)
	{
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_iNumberOfCols; ABG_iLoopCounter2++)
		{
			printf("ABG_iArray[%d][%d] = %d\n", ABG_iLoopCounter1, ABG_iLoopCounter2, ABG_iArray[ABG_iLoopCounter1][ABG_iLoopCounter2]);
		}

		printf("\n\n");
	}
	
	return(0);
}