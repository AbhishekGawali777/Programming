#include <stdio.h>

int main(void)
{
	char ABG_cArray[10];
	char *ABG_cPtrArray = NULL;
	unsigned int ABG_uiLoopCounter;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_cArray[ABG_uiLoopCounter] = (char)(ABG_uiLoopCounter + 65);

	ABG_cPtrArray = ABG_cArray;

	printf("\n\n");
	printf("Elements Of Character Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_iArray[%d] = %c\n", ABG_uiLoopCounter, *(ABG_cPtrArray + ABG_uiLoopCounter));


	printf("\n\n");
	printf("Elements Of Character Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_iArray[%d] = %c\t\tAddress = %p\n", ABG_uiLoopCounter, *(ABG_cPtrArray + ABG_uiLoopCounter),
			(ABG_cPtrArray + ABG_uiLoopCounter));

	printf("\n\n");


	return(0);
}