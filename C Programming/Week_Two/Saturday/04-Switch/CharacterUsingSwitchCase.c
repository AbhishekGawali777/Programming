#include <stdio.h>
#include <conio.h>

#define CHARACTER_ALPHABATE_UPPERCASE_BEGININNG		65
#define CHARACTER_ALPHABATE_UPPERCASE_ENDING		90

#define CHARACTER_ALPHABATE_LOWERCASE_BEGININNG		97
#define CHARACTER_ALPHABATE_LOWERCASE_ENDING		122

#define CHAR_DIGIT_BEGINING							48
#define CHAR_DIGIT_ENDING							57


int main(void)
{
	char ABG_cCh;
	unsigned int  ABG_uiValue;

	printf("\n\n");

	printf("Eneter Character : \t");
	ABG_cCh = getch();

	printf("\n\n");

	switch (ABG_cCh)
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
		printf("Character \'%c\' Entered By You, Is A VOWEL CHARACTER From The English Alphabate.!!!\n\n", ABG_cCh);
		break;

	default:
		ABG_uiValue = (int)ABG_cCh;

		if ((ABG_uiValue >= CHARACTER_ALPHABATE_UPPERCASE_BEGININNG && ABG_uiValue <= CHARACTER_ALPHABATE_UPPERCASE_ENDING)
			|| (ABG_uiValue <= CHARACTER_ALPHABATE_LOWERCASE_BEGININNG && ABG_uiValue >= CHARACTER_ALPHABATE_LOWERCASE_ENDING))
		{
			printf("Character \'%c\' Entered By You, Is A CONSONANT CHARACTER From English Alphabate ..!!!\n\n", ABG_cCh);
		}
		else if(ABG_uiValue >= CHAR_DIGIT_BEGINING && ABG_uiValue <= CHAR_DIGIT_ENDING)
		{
			printf("Character \'%c\' Entered By You, Is A DIGIT CHARACTER ...!!!\n\n", ABG_cCh);
		}
		else
		{
			printf("Character \'%c\' Entered By You, Is A SPECIAL CHARACTER ...!!!\n\n", ABG_cCh);
		}

	}

	printf("Switch Case Block Completed...!!!\n\n");

	return(0);
}