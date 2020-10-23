#include <stdio.h>
#include <stdlib.h>

#define ABG_NUM_OF_ROWS  5
#define ABG_NUM_OF_COLS  3

int main(void)
{
	unsigned int ABG_uiLoopCounter1, ABG_uiLoopCounter2;
	int** ABG_piArray = NULL;

	printf("\n\n");

	ABG_piArray = (int**)malloc(ABG_NUM_OF_ROWS * sizeof(int*));

	if (NULL == ABG_piArray)
	{
		printf("Cannot Allocate Memory For An Integer Array Of %d Rows \n\n", ABG_NUM_OF_ROWS);
		exit(-1);
	}
	else
	{
		printf("Successfully Memory Allocated For Integer Array of %d Rows...!!!\n\n", ABG_NUM_OF_ROWS);
	}

	////////////////////////		Memoy Allocation For Row		/////////////////////

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		ABG_piArray[ABG_uiLoopCounter1] = (int*)malloc(ABG_NUM_OF_COLS * sizeof(int));

		if (NULL == ABG_piArray)
		{
			printf("Cannot Allocate Memory For An Integer Array Of %d Columns\n\n", ABG_NUM_OF_COLS);
			exit(-1);
		}
		else
		{
			printf("Successfully Memory Allocated For Integer Array of %d Columns...!!!\n\n", ABG_NUM_OF_COLS);
		}
	}

	////////////////////////		Assigning Values		/////////////////////


	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		for (ABG_uiLoopCounter2 = 0; ABG_uiLoopCounter2 < ABG_NUM_OF_COLS; ABG_uiLoopCounter2++)
		{
			*(*(ABG_piArray + ABG_uiLoopCounter1) + ABG_uiLoopCounter2) =
				(ABG_uiLoopCounter1 + 1) * (ABG_uiLoopCounter2 + 1);
		}
	}

	////////////////////////		Displaying Values		/////////////////////

	printf("\n\n");
	printf("2D Integer Array Elements Along With It's Addresses Are :\n\n");

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		for (ABG_uiLoopCounter2 = 0; ABG_uiLoopCounter2 < ABG_NUM_OF_COLS; ABG_uiLoopCounter2++)
		{
			printf("ABG_piArray[%d][%d] = %d \t\t At Address &ABG_piArray[%d][%d] : %p\n",
				ABG_uiLoopCounter1,ABG_uiLoopCounter2,
				ABG_piArray[ABG_uiLoopCounter1][ABG_uiLoopCounter2],
				ABG_uiLoopCounter1, ABG_uiLoopCounter2,
				&ABG_piArray[ABG_uiLoopCounter1][ABG_uiLoopCounter2]
				);

			printf("\n");
		}
	}

	////////////////////////		Freeing Allocated Memory Of Each Row		/////////////////////

	for (ABG_uiLoopCounter1 = (ABG_NUM_OF_ROWS - 1); ABG_uiLoopCounter1 >= 0; ABG_uiLoopCounter1--)
	{
		if (*(ABG_piArray + ABG_uiLoopCounter1))
		{
			free(*(ABG_piArray + ABG_uiLoopCounter1));
			*(ABG_piArray + ABG_uiLoopCounter1) = NULL;

			printf("Memory Allocated For %d Row Has Been Freed..!!!\n", ABG_uiLoopCounter1);
		}
	}

	////////////////////////		Freeing Allocated Memory For 'ABG_piArray'		/////////////////////


	if (ABG_piArray)
	{
		free(ABG_piArray);
		ABG_piArray = NULL;
		
		printf("Memory Allocated For Row Has Been Freed..!!!\n\n\n", ABG_uiLoopCounter1);
	}

	return(0);
}