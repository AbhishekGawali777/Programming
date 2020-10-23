#include <stdio.h>
#include <ctype.h>   // Contains Declaration Of Character Checking Functions.
#include <stdlib.h> // Contains Definition OF atoi(), itoa(), exit()


int main(int argc, char* argv[], char* envp[])
{
	int ABG_iNum;
	int ABG_iSum = 0;
	int ABG_iLoopCounter;

	if (argc == 1)
	{
		printf("\n\n");
		printf("No Numbers Are Given For Addition ..!!! \n\n Exiting Now ...!!!\n\n");
		printf("USAGE : CommandLineArgumentsApplication <first number> <second number>\n\n");

		exit(0);
	}

	// *** THIS PROGRAMS ADDS ALL COMMAND LINE ARGUMENTS GIVEN IN INTEGER FORM ONLY AND OUTPUTS THE SUM***
	// *** DUE TO USE OF atoi(), ALL COMMAND LINE ARGUMENTS OF TYPES OTHER THAN 'int' ARE IGNORED * **

	printf("\n\n");
	printf("Sum Of All Integers Command Line Argument Is :\n");

	for (ABG_iLoopCounter = 1; ABG_iLoopCounter < argc; ABG_iLoopCounter++)
	{
		ABG_iNum = atoi(argv[ABG_iLoopCounter]); // atoi(const char* string);
		ABG_iSum = ABG_iSum + ABG_iNum;
	}

	printf("Sum = %d\n\n", ABG_iSum);

	return(0);
}