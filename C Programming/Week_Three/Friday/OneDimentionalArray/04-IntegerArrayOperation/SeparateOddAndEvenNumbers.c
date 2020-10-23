#include <stdio.h>

#define ABG_NUM_ELEMENTS 10

int main(void)
{
	int ABG_iArray[ABG_NUM_ELEMENTS];
	int ABG_iLoopCounter, ABG_iNumber, ABG_iSum = 0;

	printf("\n\n");
	printf("Enter Integer Elements Of Array : \n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NUM_ELEMENTS; ABG_iLoopCounter++)
	{
		scanf("%d", &ABG_iNumber);
		ABG_iArray[ABG_iLoopCounter] = ABG_iNumber;
	}

	printf("\n\n");
	printf("Even Numbers Amongst The Array Elements Are: \n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NUM_ELEMENTS; ABG_iLoopCounter++)
	{
		if ((ABG_iArray[ABG_iLoopCounter] % 2) == 0)
			printf("%d\n", ABG_iArray[ABG_iLoopCounter]);
	}

	printf("\n\n");
	printf("Odd Numbers Amongst The Array Elements Are: \n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NUM_ELEMENTS; ABG_iLoopCounter++)
	{
		if ((ABG_iArray[ABG_iLoopCounter] % 2) != 0)
			printf("%d\n", ABG_iArray[ABG_iLoopCounter]);
	}

	return(0);
}