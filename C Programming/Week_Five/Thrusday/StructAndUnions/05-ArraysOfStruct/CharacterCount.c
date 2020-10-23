#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ABG_MAX_STRING_LENGTH	512

struct ABG_CharacterCount
{
	char ABG_cCh;
	int ABG_iCharCount;
}ABG_CharacterAndCount[] = {	{'A', 0},
								{'B', 0},
								{'C', 0},
								{'D', 0}, 
								{'E', 0},
								{'F', 0},
								{'G', 0},
								{'H', 0},
								{'I', 0},
								{'J', 0},
								{'K', 0},
								{'L', 0},
								{'M', 0},
								{'N', 0},
								{'O', 0},
								{'P', 0},
								{'Q', 0},
								{'R', 0},
								{'S', 0},
								{'T', 0},
								{'U', 0},
								{'V', 0},
								{'W', 0},
								{'X', 0},
								{'Y', 0},
								{'Z', 0}, };

#define ABG_SIZEOF_ENTIRE_ARRAY_OF_STRUCTS					sizeof(ABG_CharacterAndCount)
#define ABG_SIZEOF_ONE_STRUCT_FROM_THE_ARRAY_OF_STRUCTS		sizeof(ABG_CharacterAndCount[0])
#define ABG_NUM_ELEMENTS_IN_ARRAY (ABG_SIZEOF_ENTIRE_ARRAY_OF_STRUCTS / ABG_SIZEOF_ONE_STRUCT_FROM_THE_ARRAY_OF_STRUCTS)


int main(void)
{
	char		 ABG_cString[ABG_MAX_STRING_LENGTH];
	unsigned int ABG_uiLoopCounter1, ABG_uiLoopCounter2, ABG_uiActualStringLength = 0;

	printf("\n\n");
	printf("Enter String : \t");
	gets_s(ABG_cString, ABG_MAX_STRING_LENGTH);

	ABG_uiActualStringLength = strlen(ABG_cString);

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_uiActualStringLength; ABG_uiLoopCounter1++)
	{
		for (ABG_uiLoopCounter2 = 0; ABG_uiLoopCounter2 < ABG_NUM_ELEMENTS_IN_ARRAY; ABG_uiLoopCounter2++)
		{
			ABG_cString[ABG_uiLoopCounter1] = toupper(ABG_cString[ABG_uiLoopCounter1]);

			if (ABG_cString[ABG_uiLoopCounter1] == ABG_CharacterAndCount[ABG_uiLoopCounter2].ABG_cCh)
				ABG_CharacterAndCount[ABG_uiLoopCounter2].ABG_iCharCount++;
		}
	}

	printf("\n\n");
	printf("The Number Of Occurances Of All Characters From The Alphabates Are As Follows :\n\n");

	for (ABG_uiLoopCounter1 = 0; ABG_uiLoopCounter1 < ABG_NUM_ELEMENTS_IN_ARRAY; ABG_uiLoopCounter1++)
	{
		printf("Character %c = %d\n", ABG_CharacterAndCount[ABG_uiLoopCounter1].ABG_cCh, ABG_CharacterAndCount[ABG_uiLoopCounter1].ABG_iCharCount);
	}
	printf("\n\n");


	return(0);
}