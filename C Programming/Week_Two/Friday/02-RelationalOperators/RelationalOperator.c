#include <stdio.h>

int main(int argc, char* argv[])
{
	int ABG_iNum1;
	int ABG_iNum2;
	int ABG_iResult;

	printf("\n\n");
	printf("Enter One Interger:\t");
	scanf("%d", &ABG_iNum1);

	printf("\n\n");
	printf("Enter Another Interger:\t");
	scanf("%d", &ABG_iNum2);

	printf("\n\n");
	printf("If Answer  = 0, It's 'FALSE'.\n");
	printf("If Answer  = 1, It's 'TRUE'.\n\n");

	
	ABG_iResult = (ABG_iNum1 < ABG_iNum2);
	printf("(A < B)  A = %d Is Less Than B = %d		                %d\n", ABG_iNum1, ABG_iNum2, ABG_iResult);

	ABG_iResult = (ABG_iNum1 > ABG_iNum2);
	printf("(A > B)  A = %d Is Greater Than B = %d	                 \t%d\n", ABG_iNum1, ABG_iNum2, ABG_iResult);

	ABG_iResult = (ABG_iNum1 <= ABG_iNum2);
	printf("(A <= B) A = %d Is Less Than or Equal To B = %d			%d\n", ABG_iNum1, ABG_iNum2, ABG_iResult);
	
	ABG_iResult = (ABG_iNum1 >= ABG_iNum2);
	printf("(A >= B) A = %d Is Greater Than or Equal To B = %d		%d\n", ABG_iNum1, ABG_iNum2, ABG_iResult);

	ABG_iResult = (ABG_iNum1 == ABG_iNum2);
	printf("(A == B) A = %d Is Equal To B = %d				%d\n", ABG_iNum1, ABG_iNum2, ABG_iResult);

	ABG_iResult = (ABG_iNum1 != ABG_iNum2);
	printf("(A != B) A = %d Is Not Equal To B = %d				%d\n", ABG_iNum1, ABG_iNum2, ABG_iResult);

	return(0);
}