#include <stdio.h>

int main(void)
{
	char ABG_cCh;
	int	 ABG_iNum;

	printf("\n\n");

	printf("Printing Event Numbers From 1 TO 100 For Every User Input. Exiting The Loop When User Enters 'Q' or 'q': \n\n");

	printf("Enter Charater 'Q' or 'q' To Exit Loop : \n\n");

	for (ABG_iNum = 1; ABG_iNum <= 100; ABG_iNum++)
	{
		if ((ABG_iNum % 2) != 0)
		{
			printf("\t%d\n", ABG_iNum);
			
			ABG_cCh = getch();

			if (ABG_cCh == 'Q' || ABG_cCh == 'q')
				break;
		}
	}

	printf("\n\n");
	printf("Exiting Loop...!!!");
	printf("\n\n");

	return(0);
}