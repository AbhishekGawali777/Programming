#include <stdio.h>

#define ABG_NUM_ELEMENTS 10

int main(void)
{
	int ABG_iArray[ABG_NUM_ELEMENTS];
	int ABG_iLoopCounter, ABG_iNumber, ABG_iSum = 0;

	printf("\n\n");

	printf("Enter Integer Numbers For Array :\n\n");
	
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NUM_ELEMENTS; ABG_iLoopCounter++)
	{
		scanf("%d", &ABG_iNumber);
		ABG_iArray[ABG_iLoopCounter] = ABG_iNumber;
	}

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NUM_ELEMENTS; ABG_iLoopCounter++)
	{
		ABG_iSum = ABG_iSum + ABG_iArray[ABG_iLoopCounter];
	}

	printf("\n\n");
	printf("Sum Of Array Elements In Array Is : %d", ABG_iSum);

	return(0);
}