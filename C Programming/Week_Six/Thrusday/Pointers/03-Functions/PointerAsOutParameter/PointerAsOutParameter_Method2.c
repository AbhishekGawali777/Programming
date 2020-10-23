#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// Function Declaration

	void ABG_MathematicalOperations(int, int, int*, int*, int*, int*, int*);

	// Variable Delaration

	int ABG_iNum1;
	int ABG_iNum2;
	int *ABG_iAnswerSum;
	int *ABG_iAnswerDifference;
	int *ABG_iAnswerProduct;
	int *ABG_iAnswerQuotient;
	int *ABG_iAnswerRemainder;

	printf("\n\nEnter Value For First Number : \t");
	scanf_s("%d", &ABG_iNum1);

	printf("\n\nEnter Value For Second Number : \t");
	scanf_s("%d", &ABG_iNum2);

	ABG_iAnswerSum = (int*)malloc(1 * sizeof(int));

	if (NULL == ABG_iAnswerSum)
	{
		printf("\n\nCould not Allocate Memory For 'ABG_iAnswerSum'\n\n");
		exit(0);
	}

	ABG_iAnswerDifference = (int*)malloc(1 * sizeof(int));

	if (NULL == ABG_iAnswerDifference)
	{
		printf("\n\nCould not Allocate Memory For 'ABG_iAnswerDifference'\n\n");
		exit(0);
	}

	ABG_iAnswerProduct = (int*)malloc(1 * sizeof(int));

	if (NULL == ABG_iAnswerProduct)
	{
		printf("\n\nCould not Allocate Memory For 'ABG_iAnswerProduct'\n\n");
		exit(0);
	}

	ABG_iAnswerQuotient = (int*)malloc(1 * sizeof(int));

	if (NULL == ABG_iAnswerQuotient)
	{
		printf("\n\nCould not Allocate Memory For 'ABG_iAnswerQuotient'\n\n");
		exit(0);
	}

	ABG_iAnswerRemainder = (int*)malloc(1 * sizeof(int));

	if (NULL == ABG_iAnswerRemainder)
	{
		printf("\n\nCould not Allocate Memory For 'ABG_iAnswerRemainder'\n\n");
		exit(0);
	}


	ABG_MathematicalOperations(ABG_iNum1, ABG_iNum2, ABG_iAnswerSum, ABG_iAnswerDifference, ABG_iAnswerProduct,
								ABG_iAnswerQuotient, ABG_iAnswerRemainder);

	printf("\n\n*********** Results *************\n\n");

	printf("Sum Of Given Numbers Is = %d\n", *ABG_iAnswerSum);
	printf("Difference Of Given Numbers = %d\n", *ABG_iAnswerDifference);
	printf("Product Of Given Numbers = %d\n", *ABG_iAnswerProduct);
	printf("Quotient Of Given Numbers = %d\n", *ABG_iAnswerQuotient);
	printf("Remainder Of Given Numbers = %d\n\n", *ABG_iAnswerRemainder);

	if (ABG_iAnswerRemainder)
	{
		free(ABG_iAnswerRemainder);
		ABG_iAnswerRemainder = NULL;

		printf("Memory Allocated For 'ABG_iAnswerRemainder' Is Successfully Freed..!!\n\n");
	}

	if (ABG_iAnswerQuotient)
	{
		free(ABG_iAnswerQuotient);
		ABG_iAnswerQuotient = NULL;

		printf("Memory Allocated For 'ABG_iAnswerQuotient' Is Successfully Freed..!!\n\n");
	}

	if (ABG_iAnswerProduct)
	{
		free(ABG_iAnswerProduct);
		ABG_iAnswerProduct = NULL;

		printf("Memory Allocated For 'ABG_iAnswerProduct' Is Successfully Freed..!!\n\n");
	}

	if (ABG_iAnswerDifference)
	{
		free(ABG_iAnswerDifference);
		ABG_iAnswerDifference = NULL;

		printf("Memory Allocated For 'ABG_iAnswerDifference' Is Successfully Freed..!!\n\n");
	}

	if (ABG_iAnswerSum)
	{
		free(ABG_iAnswerSum);
		ABG_iAnswerSum = NULL;

		printf("Memory Allocated For 'ABG_iAnswerSum' Is Successfully Freed..!!\n\n");
	}

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