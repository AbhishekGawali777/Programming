#include <stdio.h>

int main(void)
{
	int ABG_iArray[10];
	int *ABG_iPtrArray = NULL;
	unsigned int ABG_uiLoopCounter;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_iArray[ABG_uiLoopCounter] = (ABG_uiLoopCounter + 1) * 17;

	ABG_iPtrArray = ABG_iArray;

	printf("\n\n");
	printf("Elements Of Integer Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_iArray[%d] = %d\n", ABG_uiLoopCounter, *(ABG_iPtrArray + ABG_uiLoopCounter));


	printf("\n\n");
	printf("Elements Of Integer Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_iArray[%d] = %d\t\tAddress = %p\n", ABG_uiLoopCounter, *(ABG_iPtrArray + ABG_uiLoopCounter),
			(ABG_iPtrArray + ABG_uiLoopCounter));

	printf("\n\n");


	return(0);
}