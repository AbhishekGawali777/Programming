#include <stdio.h>

#define ABG_NUM_OF_ROWS 5
#define ABG_NUM_OF_COLS 3

int main(void)
{
	int ABG_iArray[ABG_NUM_OF_ROWS][ABG_NUM_OF_COLS];
	unsigned int ABG_uiLoopCounter1, ABG_uiLoopCounter2;

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		for (ABG_uiLoopCounter2 = 0; ABG_uiLoopCounter2 < ABG_NUM_OF_COLS; ABG_uiLoopCounter2++)
			*(ABG_iArray[ABG_uiLoopCounter1] + ABG_uiLoopCounter2) = (ABG_uiLoopCounter1 + 1) * (ABG_uiLoopCounter2 + 1);
	}

	printf("\n\n");
	printf("2D Integer Arrays Along With Addresses:\n\n");

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_OF_ROWS; ABG_uiLoopCounter1++)
	{
		for (ABG_uiLoopCounter2 = 0; ABG_uiLoopCounter2 < ABG_NUM_OF_COLS; ABG_uiLoopCounter2++)
		{
			printf("*(*(ABG_iArray + %d) + %d) = %d \t\t At Address(*(ABG_iArray + %d) + %d) :\t%p\n",
				ABG_uiLoopCounter1, ABG_uiLoopCounter2,
				*(*(ABG_iArray + ABG_uiLoopCounter1)) + ABG_uiLoopCounter2,
				ABG_uiLoopCounter1, ABG_uiLoopCounter2,
				(*(ABG_iArray + ABG_uiLoopCounter1) + ABG_uiLoopCounter2)
			);
		}
		printf("\n\n");
	}

	return(0);
}