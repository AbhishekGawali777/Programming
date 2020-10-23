#include <stdio.h>

#define MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	char ABG_cFirstString[MAX_NUMBER_OF_ELEMENTS];
	char ABG_cSecondString[MAX_NUMBER_OF_ELEMENTS];

	printf("\n\n");
	printf("Enter First String :\t");
	gets_s(ABG_cFirstString, MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n");
	printf("Enter Second String :\t");
	gets_s(ABG_cSecondString, MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n************ BEFORE CONCATENATION***************\n\n");

	printf("Entered String In First Array Is :\t%s\n\n", ABG_cFirstString);
	printf("Entered String In Second Array Is :\t%s\n\n", ABG_cSecondString);

	strcat(ABG_cFirstString, ABG_cSecondString);

	printf("\n\n************ AFTER CONCATENATION***************\n\n");

	printf("String In First Array Is :\t%s\n\n", ABG_cFirstString);
	printf("String In Second Array Is :\t%s\n\n", ABG_cSecondString);


	return(0);
}