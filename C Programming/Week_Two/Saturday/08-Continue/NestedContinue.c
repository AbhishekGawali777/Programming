#include <stdio.h>

int main(void)
{
	int ABG_iOuterLoopCounter, ABG_iInnerLoopCounter;

	printf("\n\n");

	printf("Outer Loop Prints Odd Numbers Between 1 To 10. \n\n");
	printf("Inner Loop Prints Even Numbers Between 1 To 10 For Odd Number Printed By Outer Loop.\n\n");

	for (ABG_iOuterLoopCounter = 1; ABG_iOuterLoopCounter <= 10; ABG_iOuterLoopCounter++)
	{
		if ((ABG_iOuterLoopCounter % 2) == 0)
		{
			for (ABG_iInnerLoopCounter = 1; ABG_iInnerLoopCounter <= 10; ABG_iInnerLoopCounter++)
			{
				if ((ABG_iInnerLoopCounter % 2) == 0)
					printf("\t\t%d\n", ABG_iInnerLoopCounter);
				else
					continue;
			}

			printf("\n\n");
		}
		else
			continue;
	}

	printf("\n\n");

	return(0);
}