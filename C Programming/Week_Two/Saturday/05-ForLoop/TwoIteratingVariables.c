#include <stdio.h>

int main(void)
{
	int ABG_iNum1, ABG_iNum2;

	printf("\n\n");

	printf("Printing Number 0 To 10 And 10 To 100\n\n");

	for (ABG_iNum1 = 0, ABG_iNum2 = 0; ABG_iNum1 <= 10, ABG_iNum2 <= 100; ABG_iNum1++, ABG_iNum2 += 10)
	{
		printf("\t%d\t%d\n", ABG_iNum1, ABG_iNum2);
	}

	printf("\n\n");

	return(0);
}