#include <stdio.h>
#include <conio.h>

int main(void)
{
	//variable declarations
	char ABG_cOption, ABG_cCh = '\0';
	//code
	printf("\n\n");
	printf("Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite For Loop : \n\n");
	printf("Enter 'Y' oy 'y' To Initiate User Controlled Infinite Loop : ");
	
	printf("\n\n");
	
	ABG_cOption = getch();
	if (ABG_cOption == 'Y' || ABG_cOption == 'y')
	{
		do
		{
			printf("In Loop...\n");
			ABG_cCh = getch(); //control flow waits for character input...
			if (ABG_cCh == 'Q' || ABG_cCh == 'q')
				break; //User Controlled Exitting From Infinite Loop
		} while (1); //Infinite Loop
		printf("\n\n");
		printf("EXITTING USER CONTROLLED INFINITE LOOP...");
		printf("\n\n");
	}
	else

	printf("You Must Press 'Y' or 'y' To Initiate The User Controlled Infinite Loop....Please Try Again...\n\n");
	return(0);
}