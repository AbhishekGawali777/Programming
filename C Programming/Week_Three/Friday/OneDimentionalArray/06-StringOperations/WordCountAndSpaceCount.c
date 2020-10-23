#include <stdio.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	int ABG_MyStrlen(char[]);

	char ABG_cArray[ABG_MAX_NUMBER_OF_ELEMENTS];

	int ABG_iWordCount = 0;
	int ABG_iSpaceCount = 0;
	int ABG_iLoopCounter = 0;
	int ABG_iStringLength = 0;

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cArray, ABG_MAX_NUMBER_OF_ELEMENTS);

	ABG_iStringLength = ABG_MyStrlen(ABG_cArray);

	for (ABG_iLoopCounter; ABG_iLoopCounter < ABG_iStringLength; ABG_iLoopCounter++)
	{
		switch (ABG_cArray[ABG_iLoopCounter])
		{
		case ' ':
			ABG_iSpaceCount++;
			break;
		}
	}

	ABG_iWordCount = ABG_iSpaceCount + ABG_iLoopCounter;

	printf("\n\n");
	printf("String Entered By You Is : \t");
	printf("%s\n\n", ABG_cArray);

	printf("Number Of Spaces In Input String Is : %d\n\n", ABG_iSpaceCount);
	printf("Number Of Words In Input String Is : %d\n\n", ABG_iWordCount);

	return(0);
}

int ABG_MyStrlen(char* ABG_pszArray)
{
	int ABG_iStringLength = 0;

	while (*ABG_pszArray != '\0')
	{
		*ABG_pszArray++;
		ABG_iStringLength++;
	}

	return(ABG_iStringLength);
}