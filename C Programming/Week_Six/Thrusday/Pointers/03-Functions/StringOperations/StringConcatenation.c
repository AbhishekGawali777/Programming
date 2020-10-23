#include <stdio.h>
#include <stdlib.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	// Function Declaration

	void ABG_MyStrcat(char*, char*);

	// Variable Declaration

	char* ABG_pcFirstString = NULL;
	char* ABG_pcSecondString = NULL;

	// Code

	printf("\n\n");
	ABG_pcFirstString = (char*)malloc(ABG_MAX_NUMBER_OF_ELEMENTS * sizeof(char));

	if (NULL == ABG_pcFirstString)
	{
		printf("Cannot Allocate Memory For The First Character Array...!!!\n\n");
		exit(0);
	}
	else
	{
		printf("Succesfully Allocated Memory For The First Character Array...!!!\n\n");
	}

	ABG_pcSecondString = (char*)malloc(ABG_MAX_NUMBER_OF_ELEMENTS * sizeof(char));

	if (NULL == ABG_pcSecondString)
	{
		printf("Cannot Allocate Memory For The Second Character Array...!!!\n\n");
		exit(0);
	}
	else
	{
		printf("Succesfully Allocated Memory For The Second Character Array...!!!\n\n");
	}

	
	printf("\n\n");
	printf("Enter First String :\t");
	gets_s(ABG_pcFirstString, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n");
	printf("Enter Second String :\t");
	gets_s(ABG_pcSecondString, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n************ BEFORE CONCATENATION***************\n\n");
	
	printf("Entered String In First Array Is :\t%s\n\n", ABG_pcFirstString);
	printf("Entered String In Second Array Is :\t%s\n\n", ABG_pcSecondString);

	ABG_MyStrcat(ABG_pcFirstString, ABG_pcSecondString);

	printf("\n\n************ AFTER CONCATENATION***************\n\n");

	printf("String In First Array Is :\t%s\n\n", ABG_pcFirstString);
	printf("String In Second Array Is :\t%s\n\n", ABG_pcSecondString);

	if (ABG_pcFirstString)
	{
		free(ABG_pcFirstString);
		ABG_pcFirstString = NULL;

		printf("Memory Allocated For First Array Is Freed...!!!\n\n");
	}
	
	if (ABG_pcSecondString)
	{
		free(ABG_pcSecondString);
		ABG_pcSecondString = NULL;

		printf("Memory Allocated For Second Array Is Freed...!!!\n\n");
	}

	return(0);
}

void ABG_MyStrcat(char* ABG_pszFirstString, char* ABG_pszSecondString)
{
	// Function Declaration

	int ABG_MyStrlen(char*);

	// Variable Declarations

	int ABG_iFirstStringLength;
	int ABG_iSecondStringlength;
	
	// Code 

	ABG_iFirstStringLength = ABG_MyStrlen(ABG_pszFirstString);
	ABG_iSecondStringlength = ABG_MyStrlen(ABG_pszSecondString);

	while (*ABG_pszSecondString != '\0')
		*(ABG_pszFirstString + ABG_iFirstStringLength++) = *ABG_pszSecondString++;

	*(ABG_pszFirstString + ABG_iFirstStringLength) = '\0';
}

int ABG_MyStrlen(char* ABG_pszArray)
{
	// Variable Declaration

	int ABG_iStringLength = 0;

	// Code

	while (*ABG_pszArray != '\0')
	{
		*ABG_pszArray++;
		ABG_iStringLength++;
	}

	return(ABG_iStringLength);
}