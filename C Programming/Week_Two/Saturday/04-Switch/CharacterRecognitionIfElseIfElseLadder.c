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
	unsigned int ABG_uiValue;

	printf("\n\n");

	printf("Eneter Character : \t");
	ABG_cCh = getch();

	printf("\n\n");

	if ((ABG_cCh == 'A' || ABG_cCh == 'a') || (ABG_cCh == 'E' || ABG_cCh == 'e') || (ABG_cCh == 'I' || ABG_cCh == 'i') ||
		(ABG_cCh == 'O' || ABG_cCh == 'o') || (ABG_cCh == 'U' || ABG_cCh == 'u'))
	{
		printf("Character \'%c\' Entered By You, Is A VOWEL CHARACTER From The English Alphabate.!!!\n\n", ABG_cCh);
	}
	else
	{
		ABG_uiValue = (unsigned int)ABG_cCh;

		if((ABG_uiValue >= CHARACTER_ALPHABATE_UPPERCASE_BEGININNG && ABG_uiValue <= CHARACTER_ALPHABATE_UPPERCASE_ENDING)
			&& (ABG_uiValue >= CHARACTER_ALPHABATE_LOWERCASE_BEGININNG && ABG_uiValue <= CHARACTER_ALPHABATE_LOWERCASE_ENDING))
		{
			printf("Character \'%c\' Entered By You, Is A CONSTANT CHARACTER From English Alphabate ..!!!\n\n", ABG_cCh);
		}
		else if (ABG_uiValue >= CHAR_DIGIT_BEGINING && ABG_uiValue <= CHAR_DIGIT_ENDING)
		{
			printf("Character \'%c\' Entered By You, Is A DIGIT CHARACTER ...!!!\n\n", ABG_cCh);
		}
		else
		{
			printf("Character \'%c\' Entered By You, Is A SPECIAL CHARACTER ...!!!\n\n", ABG_cCh);
		}
	}


	return(0);
}