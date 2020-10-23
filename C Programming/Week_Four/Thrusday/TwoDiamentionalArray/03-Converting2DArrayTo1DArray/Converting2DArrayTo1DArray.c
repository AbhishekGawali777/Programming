#include <stdio.h>

#define ABG_NUMBER_OF_ROWS	5
#define ABG_NUMBER_OF_COLS	3

int main(void)
{
	int ABG_iNumber;
	int ABG_iLoopCounter1;
	int ABG_iLoopCounter2;
	int ABG_i2DArray[ABG_NUMBER_OF_ROWS][ABG_NUMBER_OF_COLS];
	int ABG_i1DArray[ABG_NUMBER_OF_ROWS * ABG_NUMBER_OF_COLS];

	printf("\n\nEnter Elements Of YOur Choice To Fill Integer 2D Array : \n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUMBER_OF_ROWS; ABG_iLoopCounter1++)
	{
		printf("\n\nFor Row Number :\t%d\n\n", (ABG_iLoopCounter1 + 1));

		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_NUMBER_OF_COLS; ABG_iLoopCounter2++)
		{
			printf("Enter %d Element :", (ABG_iLoopCounter2 + 1));
			scanf("%d", &ABG_iNumber);
			ABG_i2DArray[ABG_iLoopCounter1][ABG_iLoopCounter2] = ABG_iNumber;
		}
	}

	printf("\n\n");
	printf("Two Dimentional Array Of Integers : \n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUMBER_OF_ROWS; ABG_iLoopCounter1++)
	{
		printf("For Row Number :\t%d\n\n", (ABG_iLoopCounter1 + 1));

		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_NUMBER_OF_COLS; ABG_iLoopCounter2++)
		{
			printf("ABG_i2DArray[%d][%d] = %d\n", ABG_iLoopCounter1,ABG_iLoopCounter2, ABG_i2DArray[ABG_iLoopCounter1][ABG_iLoopCounter2]);
		}
		printf("\n\n");
	}

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUMBER_OF_ROWS; ABG_iLoopCounter1++)
	{
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_NUMBER_OF_COLS; ABG_iLoopCounter2++)
		{
			ABG_i1DArray[(ABG_iLoopCounter1 * ABG_NUMBER_OF_COLS) + ABG_iLoopCounter2] = ABG_i2DArray[ABG_iLoopCounter1][ABG_iLoopCounter2];
		}
	}

	printf("One Dimentional Array Of Integers : \n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < (ABG_NUMBER_OF_ROWS * ABG_NUMBER_OF_COLS); ABG_iLoopCounter1++)
	{
		printf("ABG_i1DArray[%d] = %d", ABG_iLoopCounter1,ABG_i1DArray[ABG_iLoopCounter1]);
		printf("\n");
	}

	return(0);
}