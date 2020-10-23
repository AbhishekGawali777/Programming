#include <stdio.h>

int main(void)
{
	// Function Declaration

	void ABG_MathematicalOperations(int, int, int*, int*, int*, int*, int*);

	// Variable Delaration

	int ABG_iNum1;
	int ABG_iNum2;
	int ABG_iAnswerSum;
	int ABG_iAnswerDifference;
	int ABG_iAnswerProduct;
	int ABG_iAnswerQuotient;
	int ABG_iAnswerRemainder;

	printf("\n\nEnter Value For First Number : \t");
	scanf_s("%d", &ABG_iNum1);

	printf("\n\nEnter Value For Second Number : \t");
	scanf_s("%d", &ABG_iNum2);

	ABG_MathematicalOperations(ABG_iNum1, ABG_iNum2, &ABG_iAnswerSum, &ABG_iAnswerDifference, &ABG_iAnswerProduct,
		&ABG_iAnswerQuotient, &ABG_iAnswerRemainder);

	printf("\n\n*********** Results *************\n\n");

	printf("Sum Of Given Numbers Is = %d\n", ABG_iAnswerSum);
	printf("Difference Of Given Numbers = %d\n", ABG_iAnswerDifference);
	printf("Product Of Given Numbers = %d\n", ABG_iAnswerProduct);
	printf("Quotient Of Given Numbers = %d\n", ABG_iAnswerQuotient);
	printf("Remainder Of Given Numbers = %d\n\n", ABG_iAnswerRemainder);

	return(0);
}

void ABG_MathematicalOperations(int ABG_iNum1, int ABG_iNum2, int* ABG_Sum, int* ABG_Difference, int* ABG_Product,
	int* ABG_Quotient, int* ABG_Remainder)
{
	*ABG_Sum = ABG_iNum1 + ABG_iNum2;
	*ABG_Difference = ABG_iNum1 - ABG_iNum2;
	*ABG_Product = ABG_iNum1 * ABG_iNum2;
	*ABG_Quotient = ABG_iNum1 / ABG_iNum2;
	*ABG_Remainder = ABG_iNum1 % ABG_iNum2;
}