#include <stdio.h>

int main(void)
{
	int ABG_iOuterLoopCounter;
	int ABG_iInnerLoopCounter;

	printf("\n\n");

	printf("Printing Digits 10 To 1 And 100 To 10 \n\n");

	ABG_iOuterLoopCounter = 10;
	ABG_iInnerLoopCounter = 100;

	while (ABG_iOuterLoopCounter >= 1)
	{
		printf("\t%d\t%d\n", ABG_iOuterLoopCounter, ABG_iInnerLoopCounter);

		ABG_iOuterLoopCounter--;
		ABG_iInnerLoopCounter -= 10;
	}

	return(0);
}