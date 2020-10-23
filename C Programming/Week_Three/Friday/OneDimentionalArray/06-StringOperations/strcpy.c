#include <stdio.h>

#define MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	char ABG_cSourceArray[MAX_NUMBER_OF_ELEMENTS];
	char ABG_cDestinitionArray[MAX_NUMBER_OF_ELEMENTS];

	printf("\n\n");
	printf("Enter String :\t");
	gets(ABG_cSourceArray);

	printf("Entered String In Source Array Is :\t%s\n\n", ABG_cSourceArray);

	strcpy(ABG_cDestinitionArray, ABG_cSourceArray);

	printf("Copied String In Destinition Array Is :\t%s\n\n", ABG_cDestinitionArray);

	return(0);
}