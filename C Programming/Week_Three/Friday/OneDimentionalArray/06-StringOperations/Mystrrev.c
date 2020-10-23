#include <stdio.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	void ABG_MyStrrev(char[], char[]);

	char ABG_cSourceArray[ABG_MAX_NUMBER_OF_ELEMENTS];
	char ABG_cDestinitionArray[ABG_MAX_NUMBER_OF_ELEMENTS];

	printf("\n\n");
	printf("Enter String :\t");
	gets_s(ABG_cSourceArray, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("Entered String In Source Array Is :\t%s\n\n", ABG_cSourceArray);

	ABG_MyStrrev(ABG_cDestinitionArray, ABG_cSourceArray);

	printf("Copied String In Destinition Array Is :\t%s\n\n", ABG_cDestinitionArray);

	return(0);
}

void ABG_MyStrrev(char ABG_cDestinition[], char ABG_cSource[])
{
	int ABG_Mystrlen(char[]);

	int ABG_iLength;
	int ABG_iStringLength = 0;
	int ABG_iLoopCounter1, ABG_iLoopCounter2;

	ABG_iStringLength = ABG_MyStrlen(ABG_cSource);
	ABG_iLength = ABG_iStringLength - 1;

	for (ABG_iLoopCounter1 = 0, ABG_iLoopCounter2 = ABG_iLength;
		ABG_iLoopCounter1 < ABG_iStringLength, ABG_iLoopCounter2 >= 0;
		ABG_iLoopCounter1++, ABG_iLoopCounter2--
		)
	{
		ABG_cDestinition[ABG_iLoopCounter1] = ABG_cSource[ABG_iLoopCounter2];
	}

	ABG_cDestinition[ABG_iLoopCounter1] = '\0';
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