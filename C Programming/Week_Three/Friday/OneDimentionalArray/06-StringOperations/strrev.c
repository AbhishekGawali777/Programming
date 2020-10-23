#include <stdio.h>

#define MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	char ABG_cSourceArray[MAX_NUMBER_OF_ELEMENTS];

	printf("\n\n");
	printf("Enter String :\t");
	gets_s(ABG_cSourceArray, MAX_NUMBER_OF_ELEMENTS);

	strrev(ABG_cSourceArray);

	printf("Reversed String In Source Array Is :\t%s\n\n", ABG_cSourceArray);


	return(0);
}