#include <stdio.h>

int main(void)
{
	double ABG_dArray[10];
	unsigned int ABG_uiLoopCounter;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_dArray[ABG_uiLoopCounter] = (double)(ABG_uiLoopCounter + 1) * 1.3f;

	printf("\n\n");
	printf("Elements Of Double Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_dArray[%d] = %lf\n", ABG_uiLoopCounter, ABG_dArray[ABG_uiLoopCounter]);


	printf("\n\n");
	printf("Elements Of Double Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_dArray[%d] = %lf\t\tAddress = %p\n", ABG_uiLoopCounter, ABG_dArray[ABG_uiLoopCounter], &ABG_dArray[ABG_uiLoopCounter]);

	printf("\n\n");

	return(0);
}