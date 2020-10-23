#include<stdio.h>

int main(void)
{
	
	int ABG_OuterLoopCounter, ABG_InnerLoopCounter;
	
	printf("\n\n");
	for (ABG_OuterLoopCounter = 1; ABG_OuterLoopCounter <= 5; ABG_OuterLoopCounter++)
	{
		printf("Outer Loop Counter = %d\n", ABG_OuterLoopCounter);
		printf("--------\n\n");
		for (ABG_InnerLoopCounter = 1; ABG_InnerLoopCounter <= 7; ABG_InnerLoopCounter++)
		{
			printf("\tInner Loop Counter = %d\n", ABG_InnerLoopCounter);
		}
		printf("\n\n");
	}
	return(0);
}