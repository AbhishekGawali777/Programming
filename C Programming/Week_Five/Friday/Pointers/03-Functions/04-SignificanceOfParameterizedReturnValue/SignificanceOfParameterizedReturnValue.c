#include <stdio.h>

enum
{
	NEGATIVE = -1,
	ZERO,
	POSITIVE
};

int main(void)
{
	// Function Declarations

	int ABG_Difference(int, int, int*);

	// Variable Declaration
	
	int ABG_iNum1;
	int ABG_iNum2;
	int ABG_iAnswer;
	int ABG_iResult;

	printf("\n\nEnter Value For First Number : \t");
	scanf_s("%d", &ABG_iNum1);

	printf("\n\nEnter Value For Second Number : \t");
	scanf_s("%d", &ABG_iNum2);

	ABG_iResult = ABG_Difference(ABG_iNum1, ABG_iNum2, &ABG_iAnswer);

	printf("\n\n");
	printf("Difference Of %d And %d = %d\n\n", ABG_iNum1, ABG_iNum2, ABG_iAnswer);

	if (ABG_iResult == POSITIVE)
		printf("Difference Of %d And %d Is POSITIVE...!!!\n\n", ABG_iNum1, ABG_iNum2);
	else if(ABG_iResult == NEGATIVE)
		printf("Difference Of %d And %d Is NEGATIVE...!!!\n\n", ABG_iNum1, ABG_iNum2);
	else
		printf("Difference Of %d And %d Is ZERO...!!!\n\n", ABG_iNum1, ABG_iNum2);

	return(0);
}

int ABG_Difference(int ABG_iNum1, int ABG_iNum2, int *ABG_lpAnswer)
{
	*ABG_lpAnswer = ABG_iNum1 - ABG_iNum2;

	if (*ABG_lpAnswer < 0)
		return(NEGATIVE);
	else if (*ABG_lpAnswer > 0)
		return(POSITIVE);
	else
		return(ZERO);
}