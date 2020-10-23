#include <stdio.h>

#define ABG_NUM_ELEMENTS 10

int main(void)
{
	int ABG_iArray[ABG_NUM_ELEMENTS];
	int ABG_iLoopCounter1, ABG_iLoopCounter2, ABG_iNumber, ABG_iCount = 0;

	printf("\n\n");
	printf("Enter Integer Elements Of Array : \n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUM_ELEMENTS; ABG_iLoopCounter1++)
	{
		scanf("%d", &ABG_iNumber);

		if (ABG_iNumber < 0)
			ABG_iNumber = -1 * ABG_iNumber;

		ABG_iArray[ABG_iLoopCounter1] = ABG_iNumber;
	}

	printf("\n\n");
	printf("Array Elements Are : \n");
	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUM_ELEMENTS; ABG_iLoopCounter1++)
	{
		printf("%d\n", ABG_iArray[ABG_iLoopCounter1]);
	}

	printf("\n\n");
	printf("Prime Numbers Amongst The Array Elements Are: \n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_NUM_ELEMENTS; ABG_iLoopCounter1++)
	{
		for (ABG_iLoopCounter2 = 1; ABG_iLoopCounter2 <= ABG_iArray[ABG_iLoopCounter1]; ABG_iLoopCounter2++)
		{
			if ((ABG_iArray[ABG_iLoopCounter1] % ABG_iLoopCounter2) == 0)
				ABG_iCount++;
		}

		if (ABG_iCount == 2)
		{
			printf("%d\n", ABG_iArray[ABG_iLoopCounter1]);
		}
	
		ABG_iCount = 0;
	}

	return(0);
}