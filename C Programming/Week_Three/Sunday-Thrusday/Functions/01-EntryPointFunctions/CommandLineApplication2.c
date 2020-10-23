#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[])
{
	int ABG_iLoopCounter;

	if (argc != 4)
	{
		printf("\n\n");
		printf("Invalid Usage ...!!!\n\n Exiting Now...!!!\n\n");
		printf("USAGE: CommandLineProgramName.exe <first name> <Middle Name> <Last Name>\n\n");

		exit(0);
	}

	printf("\n\n");
	printf("Your Full Name Is :\t");

	for (ABG_iLoopCounter = 1; ABG_iLoopCounter < argc; ABG_iLoopCounter++)
	{
		printf("%s ", argv[ABG_iLoopCounter]);
	}

	printf("\n\n");

	return(0);
}