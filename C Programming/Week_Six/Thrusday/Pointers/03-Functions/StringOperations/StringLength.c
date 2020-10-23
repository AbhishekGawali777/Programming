#include <stdio.h>
#include <stdlib.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	// Function Declaration

	int ABG_MyStrlen(char*);

	// Variable Declaration

	int ABG_iLengthOfString;
	char* ABG_pcSourceArray = NULL;

	// Code

	printf("\n\n");
	ABG_pcSourceArray = (char*)malloc(ABG_MAX_NUMBER_OF_ELEMENTS * sizeof(char));

	if (NULL == ABG_pcSourceArray)
	{
		printf("Cannot Allocate Memory For The Character Array...!!!\n\n");
		exit(0);
	}
	else
	{
		printf("Succesfully Allocated Memory For The Character Array...!!!\n\n");
	}

	printf("\n\n");
	printf("Enter String :\t");
	gets_s(ABG_pcSourceArray, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\nEntered String By You Is :\t%s\n\n", ABG_pcSourceArray);

	ABG_iLengthOfString = ABG_MyStrlen(ABG_pcSourceArray);

	printf("Length Of The Entered String Is = :\t%d Characters...!!!\n\n", ABG_iLengthOfString);

	if (ABG_pcSourceArray)
	{
		free(ABG_pcSourceArray);
		ABG_pcSourceArray = NULL;

		printf("Memory Allocated For Character Array Is Freed Successfully...!!!\n\n");
	}

	return(0);
}

int ABG_MyStrlen(char* ABG_pString)
{
	// Variable Declaration
	int ABG_iStringLength = 0;

	// Code

	while (*ABG_pString++ != '\0')
		ABG_iStringLength++;

	return(ABG_iStringLength);
}