#include <stdio.h>

#define ABG_MAX_STRING_LENGTH 512

int main(void)
{
	int ABG_MyStrlen(char[]);

	int ABG_iStringLength;
	char ABG_cArray[ABG_MAX_STRING_LENGTH];

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cArray, ABG_MAX_STRING_LENGTH);

	printf("\n\n");
	printf("String Entered By You Is : \t");
	printf("%s", ABG_cArray);

	printf("\n\n");
	ABG_iStringLength = ABG_MyStrlen(ABG_cArray);
	printf("Length Of String Is = %d Characters...!!!\n\n", ABG_iStringLength);

	return(0);
}

int ABG_MyStrlen(char ABG_strArray[])
{
	int ABG_iLoopCounter;
	int ABG_iStringLength = 0;

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_MAX_STRING_LENGTH; ABG_iLoopCounter++)
	{
		if (ABG_strArray[ABG_iLoopCounter] == '\0')
			break;
		else
			ABG_iStringLength++;
	}

	return(ABG_iStringLength);
}