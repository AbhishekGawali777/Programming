#include <stdio.h>

int main(int argc, char* argv[])
{
	int ABG_iLoopCounter;

	printf("\n\n");
	printf("Hello OpenGL...!!!\n\n");
	printf("Number Of Command Line Arguments = %d\n\n", argc);

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < argc; ABG_iLoopCounter++)
	{
		printf("Command Line Argument Number %d Is %s\t\n", ABG_iLoopCounter + 1, argv[ABG_iLoopCounter]);
	}

	return(0);
}