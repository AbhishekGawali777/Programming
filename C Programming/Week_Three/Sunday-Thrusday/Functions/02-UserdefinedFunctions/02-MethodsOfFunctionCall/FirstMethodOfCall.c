#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	void	MyAddition(void);
	int		MySubtraction(void);
	void	MyMultiplication(int, int);
	int		MyDivision(int, int);

	int ABG_iResultSubstraction;
	int ABG_iNum1, ABG_iNum2;
	int ABG_iDivNumber1, ABG_iDivNumber2, ABG_iDivResult;


	MyAddition();

	ABG_iResultSubstraction = MySubtraction();
	printf("\n\n");
	
	printf("Subtraction Yields Result = %d\n", ABG_iResultSubstraction);
	
	printf("\n\n");
	
	printf("Enter Integer Value For 'A' For Multiplication : ");
	scanf("%d", &ABG_iNum1);
	
	printf("\n\n");
	
	printf("Enter Integer Value For 'B' For Multiplication : ");
	scanf("%d", &ABG_iNum2);
	MyMultiplication(ABG_iNum1, ABG_iNum2);
	
	printf("\n\n");
	
	printf("Enter Integer Value For 'A' For Division : ");
	scanf("%d", &ABG_iDivNumber1);
	
	printf("\n\n");
	
	printf("Enter Integer Value For 'B' For Division : ");
	scanf("%d", &ABG_iDivNumber2);
	
	ABG_iDivResult = MyDivision(ABG_iDivNumber1, ABG_iDivNumber2);
	
	printf("\n\n");
	
	printf("Division Of %d and %d Gives = %d (Quotient)\n", ABG_iDivNumber1, ABG_iDivNumber2, ABG_iDivResult);
	
	printf("\n\n");
	
	return(0);
}

void MyAddition(void) 
{
	int ABG_iNum1, ABG_iNum2, ABG_iSum;

	printf("\n\n");
	printf("Enter Integer Value For 'A' For Addition : ");
	scanf("%d", &ABG_iNum1);

	printf("\n\n");

	printf("Enter Integer Value For 'B' For Addition : ");
	scanf("%d", &ABG_iNum2);

	ABG_iSum = ABG_iNum1 + ABG_iNum2;

	printf("\n\n");

	printf("Sum Of %d And %d = %d\n\n", ABG_iNum1, ABG_iNum2, ABG_iSum);
}

int MySubtraction(void) 
{
	
	int ABG_iNum1, ABG_iNum2, ABG_iSub;
	
	printf("\n\n");
	
	printf("Enter Integer Value For 'A' For Subtraction : ");
	scanf("%d", &ABG_iNum1);
	
	printf("\n\n");
	
	printf("Enter Integer Value For 'B' For Subtraction : ");
	scanf("%d", &ABG_iNum2);
	
	ABG_iSub = ABG_iNum1 - ABG_iNum2;
	
	return(ABG_iSub);
}

void MyMultiplication(int ABG_iNum1, int ABG_iNum2)
{
	int ABG_iMult;

	ABG_iMult = ABG_iNum1 * ABG_iNum2;
	printf("\n\n");

	printf("Multiplication Of %d And %d = %d\n\n", ABG_iNum1, ABG_iNum2, ABG_iMult);
}

int MyDivision(int ABG_iNum1, int ABG_iNum2)
{
	int ABG_iDivQuotient;
	
	if (ABG_iNum1 > ABG_iNum2)
		ABG_iDivQuotient = ABG_iNum1 / ABG_iNum2;
	else
		ABG_iDivQuotient = ABG_iNum2 / ABG_iNum1;
	
	return(ABG_iDivQuotient);
}