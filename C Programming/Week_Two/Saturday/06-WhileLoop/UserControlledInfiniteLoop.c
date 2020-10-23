#include <stdio.h>
#include <conio.h>

int main(void)
{
	char ABG_cOption, ABG_cCh = '\0';

	printf("\n\n");
	printf("Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite For Loop:\n\n");

	printf("Enter 'Y' or 'y' To Initiate user Controlled Infinite Loop : ");
	printf("\n\n");

	ABG_cOption = getch();
	
	if (ABG_cOption == 'Y' || ABG_cOption == 'y')
	{
		while (1)
		{
			printf("In Loop...\n");
			ABG_cCh = getch();
			if (ABG_cCh == 'Q' || ABG_cCh == 'q')
				break;
		}

		printf("\n\n");
		printf("EXITING USER CONTROLLED INFINITE LOOP...");
		printf("\n\n");
	}
	else
	{
		printf("You Must Press 'Y' or 'y' To Initiate The User Controlled Infinite Loop... Please Try Again...\n\n");
	}

	return(0);
}