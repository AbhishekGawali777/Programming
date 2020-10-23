#include <stdio.h>

int main(void)
{
	int ABG_IntSize;
	int ABG_iArraySize;
	int ABG_iLoopCounter1;
	int ABG_iLoopCounter2;
	int ABG_iNumberOfRows;
	int ABG_iNumberOfCols;
	int ABG_iNumberOfElements;
	int ABG_iArray[5][3] = { {1, 2, 3}, {5, 7, 9}, {4, 6, 8}, {11, 13, 16}, {21, 24, 29} };

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

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumberOfRows; ABG_iLoopCounter1++)
	{
		printf("\t******** ROW %d ********\n\n", ABG_iLoopCounter1 + 1);
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_iNumberOfCols; ABG_iLoopCounter2++)
		{
			printf("\tABG_iArray[%d][%d] = %d\n", ABG_iLoopCounter1, ABG_iLoopCounter2, ABG_iArray[ABG_iLoopCounter1][ABG_iLoopCounter2]);
		}
		printf("\n\n");
	}

	return(0);
}