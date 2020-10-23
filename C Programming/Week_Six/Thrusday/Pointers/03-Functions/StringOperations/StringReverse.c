#include <stdio.h>
#include <stdlib.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	// Function Declaration

	void ABG_MyStrrev(char*);

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

	ABG_MyStrrev(ABG_pcSourceArray);

	printf("Reversed String Is = :\t%s \n\n", ABG_pcSourceArray);

	if (ABG_pcSourceArray)
	{
		free(ABG_pcSourceArray);
		ABG_pcSourceArray = NULL;

		printf("Memory Allocated For Character Array Is Freed Successfully...!!!\n\n");
	}

	return(0);
}

void ABG_MyStrrev(char* ABG_pString)
{
	// Function Declaration

	int ABG_MyStrlen(char*);

	// Variable Declarations

	char* ABG_pcFirstCharacter = NULL;
	char* ABG_pcLastCharacter = NULL;
	char ABG_cTempCharHolder = '\0';

	ABG_pcFirstCharacter = ABG_pString;
	ABG_pcLastCharacter = ABG_pString + ABG_MyStrlen(ABG_pString) - 1;

	while (ABG_pcFirstCharacter != ABG_pcLastCharacter)
	{
		ABG_cTempCharHolder = *ABG_pcFirstCharacter;
		*ABG_pcFirstCharacter = *ABG_pcLastCharacter;
		*ABG_pcLastCharacter = ABG_cTempCharHolder;

		ABG_pcFirstCharacter++;
		ABG_pcLastCharacter--;
	}
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