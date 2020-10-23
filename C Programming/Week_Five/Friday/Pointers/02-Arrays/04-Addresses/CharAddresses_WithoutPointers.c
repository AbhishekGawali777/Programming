#include <stdio.h>

int main(void)
{
	char ABG_cArray[10];
	unsigned int ABG_uiLoopCounter;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_cArray[ABG_uiLoopCounter] = (char)(ABG_uiLoopCounter + 65);

	printf("\n\n");
	printf("Elements Of Character Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_cArray[%d] = %c\n", ABG_uiLoopCounter, ABG_cArray[ABG_uiLoopCounter]);


	printf("\n\n");
	printf("Elements Of Character Array : \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("ABG_cArray[%d] = %c\t\tAddress = %p\n", ABG_uiLoopCounter, ABG_cArray[ABG_uiLoopCounter], &ABG_cArray[ABG_uiLoopCounter]);

	printf("\n\n");

	return(0);
}