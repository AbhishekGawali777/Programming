#include <stdio.h>

int main(void)
{
	int ABG_iNum1, ABG_iNum2;

	printf("\n\n");
	printf("Printing Digits 10 to 1 and 100 to 10: \n\n");

	ABG_iNum1 = 10;
	ABG_iNum2 = 100;

	do
	{
		printf("\t %d \t %d\n", ABG_iNum1, ABG_iNum2);
		ABG_iNum1--;
		ABG_iNum2 = ABG_iNum2 - 10;
	} while (ABG_iNum1 >= 1, ABG_iNum2 >= 10);

	printf("\n\n");
	return(0);
}