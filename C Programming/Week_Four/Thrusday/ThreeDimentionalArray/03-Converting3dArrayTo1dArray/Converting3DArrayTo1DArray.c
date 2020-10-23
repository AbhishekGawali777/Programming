#include <stdio.h>

#define ABG_NUMBER_OF_ROWS		5
#define ABG_NUMBER_OF_COLS		3
#define ABG_DEPTH				2

int main(void)
{

	int ABG_i3DArray[ABG_NUMBER_OF_ROWS][ABG_NUMBER_OF_COLS][ABG_DEPTH] = { { {101, 102}, {103, 104}, {105, 106} },
																		{ {107, 108}, {109, 110}, {15, 16} },
																		{ {48, 53}, {58, 44}, {25, 23} },
																		{ {152, 523}, { 528, 414 }, { 245, 263 } },
																		{ {483, 553}, {958, 474}, {253, 233} } };

	int ABG_iLoopCounter1;
	int ABG_iLoopCounter2;
	int ABG_iLoopCounter3;

	int ABG_i1DArray[ABG_NUMBER_OF_ROWS * ABG_NUMBER_OF_COLS * ABG_DEPTH];

	printf("\n\n");
	printf("Elements In 3D Array Are : \n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUMBER_OF_ROWS; ABG_iLoopCounter1++)
	{
		printf("\n********** ROW %d ***********\n", ABG_iLoopCounter1 + 1);

		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_NUMBER_OF_COLS; ABG_iLoopCounter2++)
		{
			printf("\n********** COLUMN %d ***********\n", ABG_iLoopCounter2 + 1);

			for (ABG_iLoopCounter3 = 0; ABG_iLoopCounter3 < ABG_DEPTH; ABG_iLoopCounter3++)
			{
				printf("ABG_i3DArray[%d][%d][%d] = %d\n", ABG_iLoopCounter1, ABG_iLoopCounter2, ABG_iLoopCounter3, ABG_i3DArray[ABG_iLoopCounter1][ABG_iLoopCounter2][ABG_iLoopCounter3]);
			}
			printf("\n");
		}
		printf("\n");
	}

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUMBER_OF_ROWS; ABG_iLoopCounter1++)
	{
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_NUMBER_OF_COLS; ABG_iLoopCounter2++)
		{
			for (ABG_iLoopCounter3 = 0; ABG_iLoopCounter3 < ABG_DEPTH; ABG_iLoopCounter3++)
			{
				ABG_i1DArray[(ABG_iLoopCounter1 * ABG_NUMBER_OF_COLS * ABG_DEPTH) + (ABG_iLoopCounter2 * ABG_DEPTH) + ABG_iLoopCounter3] =
					ABG_i3DArray[ABG_iLoopCounter1][ABG_iLoopCounter2][ABG_iLoopCounter3];
			}
		}
	}

	printf("\n\n");
	printf("Elements In 1D Array Are:\n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < (ABG_NUMBER_OF_ROWS * ABG_NUMBER_OF_COLS * ABG_DEPTH); ABG_iLoopCounter1++) 
	{
		printf("ABG_i1DArray[%d] = %d\n", ABG_iLoopCounter1, ABG_i1DArray[ABG_iLoopCounter1]);
	}


	return(0);
}