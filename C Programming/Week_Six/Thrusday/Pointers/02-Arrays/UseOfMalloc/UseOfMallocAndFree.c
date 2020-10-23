#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// Variable Declarations 

	int* ABG_piArray = NULL;
	unsigned int ABG_uiArrayLength;
	unsigned int ABG_uiLoopCounter;

	printf("\n\n");
	printf("Enter Number Of Elements You Want In Array :\t");
	scanf_s("%d", &ABG_uiArrayLength);

	ABG_piArray = (int*)malloc(ABG_uiArrayLength * sizeof(int));

	if (NULL == ABG_piArray)
	{
		printf("\n\nCannot Allocate Memory For ABG_piArray\n\n");
		exit(-1);
	}
	else
	{
		printf("\n\nMemory Allocation For Integer Array Has Successed...!!!\n\n");
		printf("Memory Address From %p To %p Have Been Allocated To Integer Array ...!!!\n\n", 
			ABG_piArray, (ABG_piArray + (ABG_uiArrayLength - 1)));
	}

	printf("\n\nEnter %d Elements For The Array :\n\n", ABG_uiArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiArrayLength; ABG_uiLoopCounter++)
	{
		printf("Enter Element Number %d:\t", ABG_uiLoopCounter + 1);
		scanf_s("%d", (ABG_piArray + ABG_uiLoopCounter));
	}

	printf("\n\n The Integer Array Entered By You, Consisting Of %d Elements :\n\n", ABG_uiArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiArrayLength; ABG_uiLoopCounter++)
		printf("ABG_piArray[%d] = %d\t\t At Address &ABG_piArray[%d] : %p\n",
		ABG_uiLoopCounter, ABG_piArray[ABG_uiLoopCounter], ABG_uiLoopCounter, &(ABG_piArray[ABG_uiLoopCounter]));

	printf("\n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiArrayLength; ABG_uiLoopCounter++)
		printf("*(ABG_piArray + %d) = %d\t\t At Address (ABG_piArray + %d) : %p\n", ABG_uiLoopCounter,
			*(ABG_piArray + ABG_uiLoopCounter), ABG_uiLoopCounter, (ABG_piArray + ABG_uiLoopCounter));

	if (ABG_piArray)
	{
		free(ABG_piArray);
		ABG_piArray = NULL;

		printf("\n\nMemory Allocated For Integer Array Is Freed Successfully..!!!\n\n");
	}

	return(0);
}