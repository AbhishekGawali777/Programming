#include <stdio.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	int ABG_MyStrlen(char[]);

	char ABG_cArray[ABG_MAX_NUMBER_OF_ELEMENTS];
	char ABG_cArraySpaceRemoved[ABG_MAX_NUMBER_OF_ELEMENTS];

	int ABG_iLoopCounter1 = 0;
	int ABG_iLoopCounter2 = 0;
	int ABG_iStringLength = 0;

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cArray, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n");
	printf("String Entered By You Is : \t");
	printf("%s\n\n", ABG_cArray);

	
	ABG_iStringLength = ABG_MyStrlen(ABG_cArray);

	for (ABG_iLoopCounter1; ABG_iLoopCounter1 < ABG_iStringLength; ABG_iLoopCounter1++)
	{
		if (ABG_cArray[ABG_iLoopCounter1] == ' ')
			continue;
		else
		{
			ABG_cArraySpaceRemoved[ABG_iLoopCounter2] = ABG_cArray[ABG_iLoopCounter1];
			ABG_iLoopCounter2++;
		}
	}

	printf("************* AFTER REMOVING SPACES IN STRING ****************");
	printf("\n\n");
	printf("String Is : \t");
	printf("%s\n\n", ABG_cArraySpaceRemoved);

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