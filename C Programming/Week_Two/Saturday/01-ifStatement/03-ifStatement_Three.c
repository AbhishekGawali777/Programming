#include <stdio.h>

int main(void)
{
	int ABG_iNum;

	printf("\n\n");

	printf("Enter Value For Num :\t");
	scanf("%d", &ABG_iNum);


	if (ABG_iNum < 0)
	{
		printf("Num = %d Is Less Than 0 (NEGATIVE).\n\n", ABG_iNum);
	}

	if (ABG_iNum < 0)
	{
		printf("Num = %d Is Less Than 0 (NEGATIVE).\n\n", ABG_iNum);
	}
	
	if (ABG_iNum > 0 && ABG_iNum <= 100)
	{
		printf("Num = %d Is Between 0 and 100.\n\n", ABG_iNum);
	}

	if ((ABG_iNum > 100) && (ABG_iNum <= 200))
	{
		printf("Num = %d Is Between 100 And 200.\n\n", ABG_iNum);
	}
	
	if ((ABG_iNum > 200) && (ABG_iNum <= 300))
	{
		printf("Num = %d Is Between 200 And 300.\n\n", ABG_iNum);
	}
	
	if ((ABG_iNum > 300) && (ABG_iNum <= 400))
	{
		printf("Num = %d Is Between 300 And 400.\n\n", ABG_iNum);
	}

	if ((ABG_iNum > 400) && (ABG_iNum <= 500))
	{
		printf("Num = %d Is Between 400 And 500.\n\n", ABG_iNum);
	}
	
	if (ABG_iNum > 0)
	{
		printf("Num = %d Is Greater Than 500 .\n\n", ABG_iNum);
	}
	
	return(0);
}