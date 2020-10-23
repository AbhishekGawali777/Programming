#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	int iLoopCounter;

	printf("\n\n");
	printf("Hello OpenGL...!!!\n\n");
	printf("Number Of Command Line Arguments = %d\n\n", argc);
	printf("Command Line Arguments Passed To This Program Are : \n\n");

	for (iLoopCounter = 0; iLoopCounter < argc; iLoopCounter++)
	{
		printf("Command Line Argument Number %d = %s\n", (iLoopCounter + 1), argv[iLoopCounter]);
	}

	printf("\n\n");

	printf("First 20 Environmental Variables Passed To This Program Are :\n\n");

	for (iLoopCounter = 0; iLoopCounter < 20; iLoopCounter++)
	{
		printf("Environmental Variable Number %d Is %s :\t\n", iLoopCounter + 1, envp[iLoopCounter]);
	}

	printf("\n\n");

	return(0);
}