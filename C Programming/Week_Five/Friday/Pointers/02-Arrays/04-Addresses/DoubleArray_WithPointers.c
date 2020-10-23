#include <stdio.h>

int main(void)
{
	double ABG_dArray[10];
	double *ABG_dPtrArray = NULL;
	unsigned int ABG_uiLoopCounter;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_dArray[ABG_uiLoopCounter] = (ABG_uiLoopCounter + 1) * 1.3f;

	ABG_dPtrArray = ABG_dArray;

	printf("\n\n");
	printf("Elements Of Double Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_dArray[%d] = %f\n", ABG_uiLoopCounter, *(ABG_dPtrArray + ABG_uiLoopCounter));


	printf("\n\n");
	printf("Elements Of Double Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_dArray[%d] = %f\t\tAddress = %p\n", ABG_uiLoopCounter, *(ABG_dPtrArray + ABG_uiLoopCounter),
			(ABG_dPtrArray + ABG_uiLoopCounter));

	printf("\n\n");


	return(0);
}