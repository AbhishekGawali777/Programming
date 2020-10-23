#include <stdio.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	void ABG_MyStrcat(char[], char[]);

	char ABG_cFirstString[ABG_MAX_NUMBER_OF_ELEMENTS];
	char ABG_cSecondString[ABG_MAX_NUMBER_OF_ELEMENTS];

	printf("\n\n");
	printf("Enter First String :\t");
	gets_s(ABG_cFirstString, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n");
	printf("Enter Second String :\t");
	gets_s(ABG_cSecondString, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n************ BEFORE CONCATENATION***************\n\n");
	
	printf("Entered String In First Array Is :\t%s\n\n", ABG_cFirstString);
	printf("Entered String In Second Array Is :\t%s\n\n", ABG_cSecondString);

	ABG_MyStrcat(ABG_cFirstString, ABG_cSecondString);

	printf("\n\n************ AFTER CONCATENATION***************\n\n");

	printf("String In First Array Is :\t%s\n\n", ABG_cFirstString);
	printf("String In Second Array Is :\t%s\n\n", ABG_cSecondString);


	return(0);
}

void ABG_MyStrcat(char ABG_FirstString[], char ABG_SecondString[])
{
	int ABG_MyStrlen(char[]);

	int ABG_iFirstStringLength;
	int ABG_iSecondStringlength;
	int ABG_iLoopCounter1, ABG_iLoopCounter2;

	ABG_iFirstStringLength = ABG_MyStrlen(ABG_FirstString);
	ABG_iSecondStringlength = ABG_MyStrlen(ABG_SecondString);

	for (ABG_iLoopCounter1 = ABG_iSecondStringlength, ABG_iLoopCounter2 = 0;
		ABG_iLoopCounter2 < ABG_iFirstStringLength; ABG_iLoopCounter1++, ABG_iLoopCounter2++)
	{
		ABG_FirstString[ABG_iLoopCounter1] = ABG_SecondString[ABG_iLoopCounter2];
	}

	ABG_FirstString[ABG_iLoopCounter1] = '\0';
}

int ABG_MyStrlen(char ABG_strArray[])
{
	int ABG_iLoopCounter;
	int ABG_iStringLength = 0;

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_MAX_NUMBER_OF_ELEMENTS; ABG_iLoopCounter++)
	{
		if (ABG_strArray[ABG_iLoopCounter] == '\0')
			break;
		else
			ABG_iStringLength++;
	}

	return(ABG_iStringLength);
}