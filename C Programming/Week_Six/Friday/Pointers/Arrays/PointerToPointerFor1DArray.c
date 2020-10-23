#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// Function Declaration

	void ABG_MyAlloc(int** ABG_ppInt, unsigned int ABG_NumberOfElements);

	// Variable Declarations

	int ABG_iLoopCounter;
	int* ABG_piArray = NULL;
	unsigned int ABG_uiNumberOfElements;

	// Code

	printf("\n\n");
	printf("How Many Elements You Want in Integer Array.? : \t");
	scanf_s("%lu", &ABG_uiNumberOfElements);

	printf("\n\n");
	ABG_MyAlloc(&ABG_piArray, ABG_uiNumberOfElements);

	printf("Enter %lu Elements To Fill Up The Integer Array\n\n", ABG_uiNumberOfElements);

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_uiNumberOfElements; ABG_iLoopCounter++)
	{
		printf("\nEnter %d Elemet In Array : \t", (ABG_iLoopCounter + 1));
		scanf_s("%d", &ABG_piArray[ABG_iLoopCounter]);
	}

	printf("\n\n");
	printf("Elements Entered By You In The Array Are:\t");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_uiNumberOfElements; ABG_iLoopCounter++)
	{
		printf(" %d ", ABG_piArray[ABG_iLoopCounter]);
	}

	printf("\n\n");

	if (NULL != ABG_piArray)
	{
		free(ABG_piArray);
		ABG_piArray = NULL;

		printf("Memory Allocated Has Been  Successfully Freed...!!!\n\n");
	}
	return(0);
}

void ABG_MyAlloc(int** ABG_ppInt, unsigned int ABG_uiNumberOfElements)
{
	*ABG_ppInt = (int*)malloc(ABG_uiNumberOfElements * sizeof(int));

	if (NULL == *ABG_ppInt)
	{
		printf("Failed To Allocate Memory ..!!!\n\n");
	}

	printf("ABG_MyAlloc() Has Successfully Allocated %lu Bytes For Integer Array...!!!\n\n",
			(ABG_uiNumberOfElements*	 sizeof(int)));
}
