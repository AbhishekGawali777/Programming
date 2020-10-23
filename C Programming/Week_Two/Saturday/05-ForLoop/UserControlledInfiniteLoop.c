#include <stdio.h>
#include <conio.h>

int main(void)
{
	char ABG_cOption, ABG_cChar = '\0';
	
	printf("\n\n");
	printf("Once The Infinite Loop Begins, Enter 'Q' or 'q' ToQuit The Infinite Loop: \n\n");

	printf("Enter 'Y' or 'y' To Initiate User Controlled infinite Loop:\t");
	printf("\n\n");

	ABG_cOption = getch();

	if (ABG_cOption == 'Y' || ABG_cOption == 'y')
	{
		for (;;)
		{
			printf("In Loop...!!!\n");
			ABG_cChar = getch();

			if ('Q' == ABG_cChar || 'q' == ABG_cChar)
				break;
		}
	}

	return(0);
}