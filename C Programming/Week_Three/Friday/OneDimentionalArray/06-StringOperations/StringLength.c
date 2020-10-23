#include <stdio.h>

#define ABG_MAX_STRING_LENGTH 512

int main(void)
{
	int ABG_iStringLength;
	char ABG_cArray[ABG_MAX_STRING_LENGTH];

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cArray, ABG_MAX_STRING_LENGTH);

	printf("\n\n");
	printf("String Entered By You Is : \t");
	printf("%s", ABG_cArray);

	printf("\n\n");
	ABG_iStringLength = strlen(ABG_cArray);
	printf("Length Of String Is = %d Characters...!!!\n\n", ABG_iStringLength);

	return(0);
}