#include <stdio.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	int ABG_MyStrlen(char[]);

	char ABG_cArray[ABG_MAX_NUMBER_OF_ELEMENTS];

	int ABG_iLoopCounter = 0;
	int ABG_iStringLength = 0;

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cArray, ABG_MAX_NUMBER_OF_ELEMENTS);
	printf("\n\n");

	printf("************** BEFORE REPLACEMENT *************\n\n");

	printf("String Is : \t");
	printf("%s\n\n", ABG_cArray);

	ABG_iStringLength = ABG_MyStrlen(ABG_cArray);

	for (ABG_iLoopCounter; ABG_iLoopCounter < ABG_iStringLength; ABG_iLoopCounter++)
	{
		switch (ABG_cArray[ABG_iLoopCounter])
		{
		case 'A':
		case 'a':
		case 'E':
		case 'e':
		case 'I':
		case 'i':
		case 'O':
		case 'o':
		case 'U':
		case 'u':
			ABG_cArray[ABG_iLoopCounter] = '*';
		}
	}

	printf("************** AFTER REPLACEMENT *************\n\n");

	printf("String Is : \t");
	printf("%s\n\n", ABG_cArray);

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