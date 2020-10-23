#include <stdio.h>
int main(void)
{
	
	int ABG_iNum1, ABG_iNum2, ABG_iNum3;
	
	ABG_iNum1 = 11;
	ABG_iNum2 = 90;
	ABG_iNum3 = 90;

	
	printf("\n\n");
	
	if (ABG_iNum1  < ABG_iNum2)
	{
		printf("Entering First if-block...\n\n");
		printf("ABG_iNum1 Is Less Than ABG_iNum2 !!!\n\n");
	}
	else
	{
		printf("Entering First else-block...\n\n");
		printf("ABG_iNum1 Is NOT Less Than ABG_iNum2 !!!\n\n");
	}
	printf("First if-else Pair Done !!!\n\n");
	
	printf("\n\n");

	if (ABG_iNum2 != ABG_iNum3)
	{
		printf("Entering Second if-block...\n\n");
		printf("ABG_iNum2 Is NOT Equal To ABG_iNum3 !!!\n\n");
	}
	else
	{
		printf("Entering Second else-block...\n\n");
		printf("ABG_iNum2 Is Equal To ABG_iNum3 !!!\n\n");
	}
	printf("Second if-else Pair Done !!!\n\n");
	
	return(0);
}