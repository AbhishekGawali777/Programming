#include <stdio.h>
#include <conio.h>

int main(void)
{
	char ABG_cOption, ABG_cCh = '\0';
	
	printf("\n\n");
	printf("Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite For Loop : \n\n");
	
	do
	{
		do
		{
			printf("\n");
			printf("In Loop...\n");
			ABG_cCh = getch();

		}while (ABG_cCh != 'Q' && ABG_cCh != 'q');
		printf("\n\n");
	
		printf("EXITTING USER CONTROLLED INFINITE LOOP...");
		printf("\n\n");
		printf("DO YOU WANT TO BEGIN USER CONTROLLED INFINITE LOOP AGAIN?...(Y/y - Yes, Any Other Key - No) : ");
		
		ABG_cOption = getch();
	
	} while (ABG_cOption == 'Y' || ABG_cOption == 'y');

	return(0);
}