#include <stdio.h>

#define MAX_NUMBER(ABG_iNum1, ABG_iNum2) ((ABG_iNum1 > ABG_iNum2) ? ABG_iNum1 : ABG_iNum2)

int main(int argc, char* argv[], char* envp[])
{
	int ABG_iNum1;
	int ABG_iNum2;
	int ABG_iResult;

	float ABG_fNum1;
	float ABG_fNum2;
	float ABG_fResult;

	printf("\n\n");
	printf("Enter An Integer Number : \n\n");
	scanf("%d", &ABG_iNum1);

	printf("\n\n");

	printf("Enter Another Integer Number : \n\n");
	scanf("%d", &ABG_iNum2);

	ABG_iResult = MAX_NUMBER(ABG_iNum1, ABG_iNum2);

	printf("\n\n");

	printf("Result Of Macro Function MAX_NUMBER() = %d\n", ABG_iResult);
	printf("\n\n");

	printf("Enter A Floating Point Number : \n\n");
	scanf("%f", &ABG_fNum1);

	printf("\n\n");

	printf("Enter Another Floating Point Number : \n\n");
	scanf("%f", &ABG_fNum2);

	ABG_fResult = MAX_NUMBER(ABG_fNum1, ABG_fNum2);

	printf("\n\n");

	printf("Result Of Macro Function MAX_NUMBER() = %f\n", ABG_fResult);

	printf("\n\n");

	return(0);
}