#include <stdio.h>
#include <stdlib.h>

#define ABG_MAX_STRING_LENGTH 256

int main(void)
{
	// Function Declaration

	char* ABG_ReplaceVowelsWithHashSymbol(char*);

	// Variable Declaration

	char ABG_cString[ABG_MAX_STRING_LENGTH];
	char* ABG_pszReplacedString = NULL;

	// Code

	printf("\n\n");
	printf("Enter String:\t");
	gets_s(ABG_cString, ABG_MAX_STRING_LENGTH);

	ABG_pszReplacedString = ABG_ReplaceVowelsWithHashSymbol(ABG_cString);

	if (NULL == ABG_pszReplacedString)
	{
		printf("ABG_ReplaceVowelsWithHashSysmobl() Function Has Failed..!!!\n\n");
		exit(0);
	}

	printf("\n\nReplaced String Is:\t%s\n\n", ABG_pszReplacedString);

	if (ABG_pszReplacedString)
	{
		free(ABG_pszReplacedString);
		ABG_pszReplacedString = NULL;
	}

	return(0);
}

char* ABG_ReplaceVowelsWithHashSymbol(char* ABG_pszString)
{
	// Function Declarations

	int ABG_MyStrlen(char*);
	void ABG_MyStrcpy(char*, char*);

	// Variable Declarations
	int ABG_iLoopCounter;
	char* ABG_pszNewString = NULL;

	ABG_pszNewString = (char*)malloc(ABG_MyStrlen(ABG_pszString) * sizeof(char));

	if (NULL == ABG_pszNewString)
	{
		printf("Could Not Allocate Memory For New String..!!!\n\n");
		return(NULL);
	}

	ABG_MyStrcpy(ABG_pszNewString, ABG_pszString);

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_MyStrlen(ABG_pszNewString); ABG_iLoopCounter++)
	{
		switch (ABG_pszString[ABG_iLoopCounter])
		{
		case 'A':
		case'a':
		case'E':
		case'e':
		case'I':
		case'i':
		case'O':
		case'o':
		case'U':
		case'u':
			ABG_pszNewString[ABG_iLoopCounter] = '#';
			break;
		default:
			break;
		}
	}

	return(ABG_pszNewString);
}

void ABG_MyStrcpy(char* ABG_pszDestinationString, char* ABG_pszSourceString)
{
	// Code 

	while (*ABG_pszSourceString != '\0')
		*ABG_pszDestinationString++ = *ABG_pszSourceString++;

	*ABG_pszDestinationString = '\0';
}

int ABG_MyStrlen(char* ABG_pszString)
{
	// Variable Declaration

	int ABG_uiStringLength = 0;
	
	while (*ABG_pszString++ != '\0')
		ABG_uiStringLength++;

	return(ABG_uiStringLength);
}