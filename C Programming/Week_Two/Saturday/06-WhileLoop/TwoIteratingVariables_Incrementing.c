#include <stdio.h>

int main(void)
{
	int ABG_iOuterLoopCounter;
	int ABG_iInnerLoopCounter;

	printf("\n\n");

	printf("Printing Digits 1 To 10 \n\n");

	ABG_iOuterLoopCounter = 1;
	ABG_iInnerLoopCounter = 10;

	while (ABG_iOuterLoopCounter <= 10)
	{
		printf("\t%d\t%d\n", ABG_iOuterLoopCounter, ABG_iInnerLoopCounter);

		ABG_iOuterLoopCounter++;
		ABG_iInnerLoopCounter += 10;
	}

	return(0);
}