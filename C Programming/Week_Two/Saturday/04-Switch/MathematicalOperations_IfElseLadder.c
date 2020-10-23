#include <stdio.h>
#include <conio.h>

int main(void)
{
	int ABG_iNum1, ABG_iNum2;
	int ABG_iResult;

	char ABG_cOption, ABG_cOptionDivision;
	printf("\n\n");

	printf("Enter Valur For 'A' :\t");
	scanf("%d", &ABG_iNum1);

	printf("Enter Valur For 'B' :\t");
	scanf("%d", &ABG_iNum2);

	printf("Enter Option In Character : \n\n");
	printf("'A' or 'a' For Addition : \n");
	printf("'S' or 's' For Subtraction : \n");
	printf("'M' or 'm' For Multiplication : \n");
	printf("'D' or 'd' For Division : \n\n");

	printf("Enter Option : ");
	ABG_cOption = getch();

	printf("\n\n");
	if (ABG_cOption == 'A' || ABG_cOption == 'a')
	{
		ABG_iResult = ABG_iNum1 + ABG_iNum2;
		printf("Addition Of A = %d And B = %d Gives Result %d !!!\n\n", ABG_iNum1, ABG_iNum2,
			ABG_iResult);
	}
	else if (ABG_cOption == 'S' || ABG_cOption == 's')
	{
		if (ABG_iNum1 >= ABG_iNum2)
		{
			ABG_iResult = ABG_iNum1 - ABG_iNum2;
			printf("Subtraction Of B = %d From A = %d Gives Result %d !!!\n\n", ABG_iNum2, ABG_iNum1, ABG_iResult);
		}
		else
		{
			ABG_iResult = ABG_iNum2 - ABG_iNum1;
			printf("Subtraction Of A = %d From B = %d Gives Result %d !!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
		}
	}
	else if (ABG_cOption == 'M' || ABG_cOption == 'm')
	{
		ABG_iResult = ABG_iNum1 * ABG_iNum2;
		printf("Multiplication Of A = %d And B = %d Gives Result %d !!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
	}
	else if (ABG_cOption == 'D' || ABG_cOption == 'd')
	{
		printf("Enter Option In Character : \n\n");
		printf("'Q' or 'q' or '/' For Quotient Upon Division : \n");
		printf("'R' or 'r' or '%%' For Remainder Upon Division : \n");
		printf("Enter Option : ");

		ABG_cOptionDivision = getch();

		printf("\n\n");
		if (ABG_cOptionDivision == 'Q' || ABG_cOptionDivision == 'q' || ABG_cOptionDivision
			== '/')
		{
			if (ABG_iNum1 >= ABG_iNum2)
			{
				ABG_iResult = ABG_iNum1 / ABG_iNum2;
				printf("Division Of A = %d By B = %d Gives Quotient = %d !!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
			}
			else
			{
				ABG_iResult = ABG_iNum2 / ABG_iNum1;
				printf("Division Of B = %d By A = %d Gives Quotient = %d !!!\n	\n", ABG_iNum2, ABG_iNum1, ABG_iResult);
			}
		}
		else if (ABG_cOptionDivision == 'R' || ABG_cOptionDivision == 'r' || ABG_cOptionDivision == '%')
		{
			if (ABG_iNum1 >= ABG_iNum2)
			{
				ABG_iResult = ABG_iNum1 % ABG_iNum2;
				printf("Division Of A = %d By B = %d Gives Remainder = %d !!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
			}
			else
			{
				ABG_iResult = ABG_iNum2 % ABG_iNum1;
				printf("Division Of B = %d By A = %d Gives Remainder = %d !!!\n\n", ABG_iNum2, ABG_iNum1, ABG_iResult);
			}
		}
		else
			printf("Invalid Character %c Entered For Division !!! Please Try Again...\n\n", ABG_cOptionDivision);
	}
	else
	{
		printf("Invalid Character %c Entered !!! Please Try Again...\n\n", ABG_cOption);
	}

	printf("If - Else If - Else Ladder Complete !!!\n");

	return(0);
}