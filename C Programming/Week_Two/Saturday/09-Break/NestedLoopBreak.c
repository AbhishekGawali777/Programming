#include <stdio.h>

int main(void)
{
	int ABG_iOuterLoopCounter, ABG_iInnerLoopCounter;

	printf("\n\n");

	for (ABG_iOuterLoopCounter = 1; ABG_iOuterLoopCounter <= 20; ABG_iOuterLoopCounter++)
	{
		for (ABG_iInnerLoopCounter = 1; ABG_iInnerLoopCounter <= 10; ABG_iInnerLoopCounter++)
		{
			if (ABG_iInnerLoopCounter > 1)
				break;
			else
				printf("\t\t $ ");
		}
		printf("\n\n");
	}

	printf("\n\n");

	return(0);
}