#include <stdio.h>
#include <stdlib.h>

#define ABG_NUM_OF_ROWS 	5
#define ABG_NUM_OF_COLS		3

int main(void)
{
	int* ABG_piArray[ABG_NUM_OF_ROWS];
	unsigned int ABG_uiLoopCounter1, ABG_uiLoopCounter2;

	printf("\n\n");
	
	///////////////////			Allocating Memory To 2D Array			///////////////////////

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		ABG_piArray[ABG_uiLoopCounter1] = (int*)malloc(ABG_NUM_OF_COLS * sizeof(int));

		if (NULL == ABG_piArray[ABG_uiLoopCounter1])
		{
			printf("Cannot Allocate Memory For Row %d Of 2D Integer Array ...!!!\n\n", ABG_uiLoopCounter1);
			exit(-1);
		}
		else
		{
			printf("Successfully Allocated Memory To Row %d of 2D Integer Array...!!! \n\n", ABG_uiLoopCounter1);
		}
	}

	///////////////////			Assigning Values To 2D Array			///////////////////////

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		for (ABG_uiLoopCounter2 = 0; ABG_uiLoopCounter2 < ABG_NUM_OF_COLS; ABG_uiLoopCounter2++)
		{
			ABG_piArray[ABG_uiLoopCounter1][ABG_uiLoopCounter2] = (ABG_uiLoopCounter1 + 1) * (ABG_uiLoopCounter2 + 1);
		}
	}

	///////////////////			Displaying Values Of 2D Array			///////////////////////

	printf("\n\n");
	printf("Displaying 2D Array:\n\n");

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		for (ABG_uiLoopCounter2 = 0; ABG_uiLoopCounter2 < ABG_NUM_OF_COLS; ABG_uiLoopCounter2++)
		{
			printf("ABG_piArray[%d][%d] = %d\n", ABG_uiLoopCounter1, ABG_uiLoopCounter2,
					ABG_piArray[ABG_uiLoopCounter1][ABG_uiLoopCounter2]);
		}

		printf("\n\n");
	}

	///////////////////			Freeing Values Of 2D Array			///////////////////////


	printf("\n\n");

	for (ABG_uiLoopCounter1 = (ABG_NUM_OF_ROWS - 1); ABG_uiLoopCounter1 >= 0; ABG_uiLoopCounter1--)
	{
		free(ABG_piArray[ABG_uiLoopCounter1]);
		ABG_piArray[ABG_uiLoopCounter1] = NULL;	

		printf("Memory Allocated To Row %d Of 2D Integer Array Has Been Successully Freed...!!!\n", ABG_uiLoopCounter1);
	}

	return(0);
}