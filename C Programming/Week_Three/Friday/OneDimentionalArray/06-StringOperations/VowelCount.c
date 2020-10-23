#include <stdio.h>

#define ABG_MAX_NUMBER_OF_ELEMENTS 256

int main(void)
{
	int ABG_MyStrlen(char[]);

	char ABG_cArray[ABG_MAX_NUMBER_OF_ELEMENTS];

	int ABG_iCount_a = 0;
	int ABG_iCount_e = 0;
	int ABG_iCount_i = 0;
	int ABG_iCount_o = 0;
	int ABG_iCount_u = 0;
	int ABG_iLoopCounter = 0;
	int ABG_iStringLength = 0;

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cArray, ABG_MAX_NUMBER_OF_ELEMENTS);

	printf("\n\n");
	printf("String Entered By You Is : \t");
	printf("%s", ABG_cArray);

	ABG_iStringLength = ABG_MyStrlen(ABG_cArray);

	for (ABG_iLoopCounter; ABG_iLoopCounter < ABG_iStringLength; ABG_iLoopCounter++)
	{
		switch (ABG_cArray[ABG_iLoopCounter])
		{
		case 'A':
		case 'a':
			ABG_iCount_a++;
			break;
		case 'E':
		case 'e':
			ABG_iCount_e++;
			break;
		case 'I':
		case 'i':
			ABG_iCount_i++;
			break;
		case 'O':
		case 'o':
			ABG_iCount_o++;
			break;
		case 'U':
		case 'u':
			ABG_iCount_u++;
			break;
		}
	}

	printf("\n\n");
	printf("in String Entered By You, The Vowels And THe Number Of Vowels Are As Follows : \n\n");

	printf("'A' Has Occured %d Times...!!!\n\n", ABG_iCount_a);
	printf("'E' Has Occured %d Times...!!!\n\n", ABG_iCount_e);
	printf("'I' Has Occured %d Times...!!!\n\n", ABG_iCount_i);
	printf("'O' Has Occured %d Times...!!!\n\n", ABG_iCount_o);
	printf("'U' Has Occured %d Times...!!!\n\n", ABG_iCount_u);

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