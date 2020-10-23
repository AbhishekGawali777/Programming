#include <stdio.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	void ABG_MyStrcpy(char[], char[]);

	char ABG_cSourceArray[ABG_MAX_NUMBER_OF_ELEMENTS];
	char ABG_cDestinitionArray[ABG_MAX_NUMBER_OF_ELEMENTS];

	printf("\n\n");
	printf("Enter String :\t");
	gets(ABG_cSourceArray);

	printf("Entered String In Source Array Is :\t%s\n\n", ABG_cSourceArray);

	ABG_MyStrcpy(ABG_cDestinitionArray, ABG_cSourceArray);

	printf("Copied String In Destinition Array Is :\t%s\n\n", ABG_cDestinitionArray);

	return(0);
}

void ABG_MyStrcpy(char ABG_DestinitionArray[], char ABG_SourceArray[])
{
	int ABG_MyStrlen(char[]);
	
	int ABG_iLoopCounter;
	int ABG_iStringLength = 0;
	
	ABG_iStringLength = ABG_MyStrlen(ABG_SourceArray);
	
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_iStringLength; ABG_iLoopCounter++)
		ABG_DestinitionArray[ABG_iLoopCounter] = ABG_SourceArray[ABG_iLoopCounter];
	
	ABG_DestinitionArray[ABG_iLoopCounter] = '\0';
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