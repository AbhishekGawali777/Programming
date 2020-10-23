#include <stdio.h>
#include <conio.h>

int main(void)
{
	int ABG_iNum1, ABG_iNum2;
	int ABG_iResult;

	char ABG_cOption, ABG_cOptionDivision;

	printf("\n\n");

	printf("Enter Value For 'A' :\t");
	scanf("%d", &ABG_iNum1);

	printf("Enter Value For 'B' :\t");
	scanf("%d", &ABG_iNum2);

	printf("Enter Option in Character : \n\n");
	printf("'A' Or 'a' For Addition : \n");
	printf("'S' Or 's' For Subtraction : \n");
	printf("'M' Or 'm' For Multiplication : \n");
	printf("'D' Or 'd' For Division : \n");

	printf("Enter Option ");
	ABG_cOption = getch();

	switch (ABG_cOption)
	{
	case 'A':
	case'a':
		ABG_iResult = ABG_iNum1 + ABG_iNum2;
		printf("Addition Of A = %d And B = %d Gives Result = %d.!!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
		break;

	case 'S':
	case 's':
		if (ABG_iNum1 > ABG_iNum2)
		{
			ABG_iResult = ABG_iNum1 - ABG_iNum2;
			printf("Subtraction Of B = %d From A = %d Gives Result = %d.!!!\n\n", ABG_iNum2, ABG_iNum1, ABG_iResult);
		}
		else
		{
			ABG_iResult = ABG_iNum2 - ABG_iNum1;
			printf("Subtraction Of A = %d From B = %d Gives Result = %d.!!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
		}
		break;

	case 'M':
	case 'm':
		ABG_iResult = ABG_iNum1 * ABG_iNum2;
		printf("Multiplication Of A = %d And B = %d Gives Result = %d.!!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
		break;

	case 'D':
	case 'd':
		printf("Enter Option In Character : \n\n");
		printf("'Q' or 'q' or '/' For Quotient Upon Division : \n");
		printf("'R' or 'r' or '%%' For Remainder Upon Division : \n");
		printf("Enter Option : ");
		
		ABG_cOptionDivision = getch();

		printf("\n\n");
	
		switch (ABG_cOptionDivision)
		{
		case 'Q':
		case 'q':
		case '/':
			if (ABG_iNum1 > ABG_iNum2)
			{
				ABG_iResult = ABG_iNum1 / ABG_iNum2;
				printf("Division Of A = %d By B = %d Gives Quotient = %d.!!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
			}
			else
			{
				ABG_iResult = ABG_iNum2 / ABG_iNum1;
				printf("Subtraction Of B = %d By A = %d Gives Quotient = %d.!!!\n\n", ABG_iNum2, ABG_iNum1, ABG_iResult);
			}
			break;

		case 'R':
		case 'r':
		case '%':
			if (ABG_iNum1 > ABG_iNum2)
			{
				ABG_iResult = ABG_iNum1 % ABG_iNum2;
				printf("Division Of A = %d By B = %d Gives Remainder = %d.!!!\n\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
			}
			else
			{
				ABG_iResult = ABG_iNum2 % ABG_iNum1;
				printf("Division Of B = %d By A = %d Gives Remainder = %d.!!!\n\n", ABG_iNum2, ABG_iNum1, ABG_iResult);
			}
			break;

		default:
			printf("Invalid Character %c Entered For Division !!! Please Try Again...\n\n", ABG_cOptionDivision);
				break; 
		}
		break;
	default:

		printf("Invalid Character %c Entered !!! Please Try Again...\n\n", ABG_cOption);
		break;
	}

	printf("Switch case Block Complete ...!!\n\n");

	return(0);
}