#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// Function Declarations

	void ABG_MultiplyArrayElementsByNumber(int*, int, int);

	// Variable Declarations

	int ABG_iNum;
	int ABG_iLoopCounter;
	int* ABG_iArray = NULL;
	int ABG_NumberOfElements;

	// Code

	printf("\n\n");
	
	printf("How Many Elements You Want In Array.?:\t");
	scanf_s("%d", &ABG_NumberOfElements);

	ABG_iArray = (int*)malloc(ABG_NumberOfElements * sizeof(int));

	if (NULL == ABG_iArray)
	{
		printf("Cannot Allocate Memory For Integer Array...!!!\n\n");
		exit(0);
	}
	else
	{
		printf("Succesfully Allocated Memory For Integer Array...!!!\n\n");
	}

	printf("\n\n");
	printf("Enter %d Elements For Integer Array : \n\n", ABG_NumberOfElements);

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NumberOfElements; ABG_iLoopCounter++)
	{
		printf("\nEnter Element Number %d : \t", ABG_iLoopCounter);
		scanf_s("%d", &ABG_iArray[ABG_iLoopCounter]);
	}

	printf("\n\n");
	printf("Array Before Passing ABG_MultiplyArrayElementsByNumber().\n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NumberOfElements; ABG_iLoopCounter++)
	{
		printf("ABG_iArray[%d] : = %d\n", ABG_iLoopCounter, ABG_iArray[ABG_iLoopCounter]);
		
	}

	printf("\n\n");
	printf("Enter Number From Which You Want To Multiply Each Element Of Array : \t");
	scanf_s("%d", &ABG_iNum);

	ABG_MultiplyArrayElementsByNumber(ABG_iArray, ABG_NumberOfElements, ABG_iNum);

	printf("\n\n");
	printf("Array Returned By Function ABG_MultiplyArrayElemetsByNumber():\n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NumberOfElements; ABG_iLoopCounter++)
		printf("ABG_iArray[%d] = %d\n", ABG_iLoopCounter, ABG_iArray[ABG_iLoopCounter]);

	if(ABG_iArray)
	{
		free(ABG_iArray);
		ABG_iArray = NULL;

		printf("\n\nMemory Allocated For Array is Freed Succesfully...!!!\n\n");
	}

	return(0);
}

void ABG_MultiplyArrayElementsByNumber(int* ABG_pIntegerArray, int ABG_NumberOfElements, int ABG_iNumber)
{
	// Variable Declaration

	int ABG_iLoopCounter;

	// Code 

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NumberOfElements; ABG_iLoopCounter++)
	{
		ABG_pIntegerArray[ABG_iLoopCounter] = ABG_pIntegerArray[ABG_iLoopCounter] * ABG_iNumber;
	}
}