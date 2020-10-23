#include <stdio.h>

int main(void)
{
	float ABG_fArray[10];
	float* ABG_fPtrArray = NULL;
	unsigned int ABG_uiLoopCounter;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_fArray[ABG_uiLoopCounter] = (ABG_uiLoopCounter + 1) * 1.7f;

	ABG_fPtrArray = ABG_fArray;

	printf("\n\n");
	printf("Elements Of Floating-Point Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_fArray[%d] = %f\n", ABG_uiLoopCounter, *(ABG_fPtrArray + ABG_uiLoopCounter));


	printf("\n\n");
	printf("Elements Of Floating-Point Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_fArray[%d] = %f\t\tAddress = %p\n", ABG_uiLoopCounter, *(ABG_fPtrArray + ABG_uiLoopCounter),
			(ABG_fPtrArray + ABG_uiLoopCounter));

	printf("\n\n");


	return(0);
}