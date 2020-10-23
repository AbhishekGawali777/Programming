#include <stdio.h>

int main(void)
{
	//variable declarations
	int ABG_OuterLoopCounter, ABG_FirstInnerLoopCounter, ABG_SecondInnerLoopCounter;
	//code
	printf("\n\n");
	for (ABG_OuterLoopCounter = 1; ABG_OuterLoopCounter <= 4; ABG_OuterLoopCounter++)
	{
		printf("Outer Loop Counter = %d\n", ABG_OuterLoopCounter);
		printf("--------\n\n");
		for (ABG_FirstInnerLoopCounter = 1; ABG_FirstInnerLoopCounter <= 5; ABG_FirstInnerLoopCounter++)
		{
			printf("\tFirst Inner Loop Counter = %d\n", ABG_FirstInnerLoopCounter);
			printf("\t--------\n\n");
			for (ABG_SecondInnerLoopCounter = 1; ABG_SecondInnerLoopCounter <= 7; ABG_SecondInnerLoopCounter++)
			{
				printf("\t\tSecond Inner Loop Counter = %d\n", ABG_SecondInnerLoopCounter);
			}
			printf("\n\n");
		}
		printf("\n\n");
	}
	return(0);
}