#include <stdio.h>
int main(void)
{

	int ABG_iNum1, ABG_iNum2, ABG_iNum3;

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
			printf("\t--------\n\n");

			ABG_iNum3 = 1;

			do
			{
				printf("\t\tk = %d\n", ABG_iNum3);
				ABG_iNum3++;
			} while (ABG_iNum3 <= 2);

			printf("\n\n");

			ABG_iNum2++;
		} while (ABG_iNum2 <= 3);

		printf("\n\n");

		ABG_iNum1++;

	} while (ABG_iNum1 <= 5);

	return(0);
}