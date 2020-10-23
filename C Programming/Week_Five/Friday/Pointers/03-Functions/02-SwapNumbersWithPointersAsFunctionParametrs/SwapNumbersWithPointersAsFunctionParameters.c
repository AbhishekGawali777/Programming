#include <stdio.h>

int main(void)
{
	// Function Declaration

	void ABG_SwapNumbers(int*, int*);

	// Variable Defclarations

	int ABG_iNum1, ABG_iNum2;

	printf("\n\nEnter Value For First Number : \t");
	scanf_s("%d", &ABG_iNum1);

	printf("\n\nEnter Value For Second Number : \t");
	scanf_s("%d", &ABG_iNum2);

	printf("\n\n*********** BEFORE SWAPPING ************ \n\n");
	printf("Value Of First Number Is : %d\n", ABG_iNum1);
	printf("Value Of Second	Number Is : %d\n\n", ABG_iNum2);

	ABG_SwapNumbers(&ABG_iNum1, &ABG_iNum2);

	printf("\n\n*********** AFTER SWAPPING ************ \n\n");
	printf("Value Of First Number Is : %d\n", ABG_iNum1);
	printf("Value Of Second	Number Is : %d\n\n", ABG_iNum2);

	return(0);
}

void ABG_SwapNumbers(int *ABG_iNum1, int *ABG_iNum2)
{
	// Variable Declaration
	int ABG_iTemp;

	printf("\n\n*********** BEFORE SWAPPING ************ \n\n");
	printf("Value Of First  Formal Parameter Number Is : %d\n", *ABG_iNum1);
	printf("Value Of Second Formal Parameter Number Is : %d\n\n", *ABG_iNum2);

	ABG_iTemp = *ABG_iNum1;
	*ABG_iNum1 = *ABG_iNum2;
	*ABG_iNum2 = ABG_iTemp;

	printf("\n\n*********** AFTER SWAPPING ************ \n\n");
	printf("Value Of First  Formal Parameter Number Is : %d\n", *ABG_iNum1);
	printf("Value Of Second Formal Parameter Number Is : %d\n\n", *ABG_iNum2);

}