#include <stdio.h>
#include <stdlib.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	// Function Declaration

	void ABG_MyStrcpy(char*, char*);

	// Variable Declaration

	char* ABG_pcSourceArray = NULL;
	char* ABG_pcDestinationArray = NULL;

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

	ABG_pcDestinationArray = (char*)malloc(ABG_MAX_NUMBER_OF_ELEMENTS * sizeof(char));

	if (NULL == ABG_pcSourceArray)
	{
		printf("Cannot Allocate Memory For The Destination Character Array...!!!\n\n");
		exit(0);
	}
	else
	{
		printf("Succesfully Allocated Memory For The Destination Character Array...!!!\n\n");
	}

	printf("\n\n");
	printf("Enter Source  String :\t");
	gets_s(ABG_pcSourceArray, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\nEntered String In Source Array Is :\t%s\n\n", ABG_pcSourceArray);

	ABG_MyStrcpy(ABG_pcDestinationArray, ABG_pcSourceArray);

	printf("\n\nCopied String In Destinition Array Is :\t%s\n\n", ABG_pcDestinationArray);

	if (ABG_pcSourceArray)
	{
		free(ABG_pcSourceArray);
		ABG_pcSourceArray = NULL;

		printf("Memory Allocated For Source Character Array Is Freed Successfully...!!!\n\n");

	}

	if (ABG_pcDestinationArray)
	{
		free(ABG_pcDestinationArray);
		ABG_pcDestinationArray = NULL;

		printf("Memory Allocated For Destination Character Array Is Freed Successfully...!!!\n\n");

	}

	return(0);
}

void ABG_MyStrcpy(char* ABG_pDestinitionArray, char* ABG_pSourceArray)
{
	while (*ABG_pSourceArray != '\0')
		*ABG_pDestinitionArray++ = *ABG_pSourceArray++;

	*ABG_pDestinitionArray = '\0';
}
