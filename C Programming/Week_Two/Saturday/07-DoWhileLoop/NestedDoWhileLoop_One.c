#include <stdio.h>

int main(void)
{

	int ABG_iNum1, ABG_iNum2;

	printf("\n\n");

	ABG_iNum1 = 1;

	do
	{
		printf("i = %d\n", ABG_iNum1);
		printf("--------\n\n");

		ABG_iNum2 = 1;

		do
		{
			printf("\tj = %d\n", ABG_iNum2);
			
			ABG_iNum2++;
		} while (ABG_iNum2 <= 5);
		
		ABG_iNum1++;
		
		printf("\n\n");
	} while (ABG_iNum1 <= 10);
	
	return(0);
}