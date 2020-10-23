#include <stdio.h>

int main(void)
{

	int ABG_OuterLoopCounter, ABG_InnerLoopCounter, ABG_iValue;

	printf("\n\n");
	
	for (ABG_OuterLoopCounter = 0; ABG_OuterLoopCounter < 64; ABG_OuterLoopCounter++)
	{
		for (ABG_InnerLoopCounter = 0; ABG_InnerLoopCounter < 64; ABG_InnerLoopCounter++)
		{
			ABG_iValue = ((ABG_OuterLoopCounter & 0x8) == 0) ^ ((ABG_InnerLoopCounter & 0x8) == 0);

			if (ABG_iValue == 0)
				printf(" ");
			if (ABG_iValue == 1)
				printf("*");
		}
		printf("\n\n");
	}

	return(0);
}