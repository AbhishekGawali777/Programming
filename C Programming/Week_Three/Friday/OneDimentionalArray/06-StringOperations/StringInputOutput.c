#include <stdio.h>

#define ABG_MAX_STRING_LENGTH 512

int main(void)
{
	char ABG_cArray[ABG_MAX_STRING_LENGTH];

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cArray, ABG_MAX_STRING_LENGTH);

	printf("\n\n");
	printf("String Entered By You Is : \t");
	puts(ABG_cArray, ABG_MAX_STRING_LENGTH);
	//printf("%s", ABG_cArray);

	return(0);
}