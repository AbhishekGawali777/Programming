#include <stdio.h>

int main(void)
{
	int ABG_iNum;

	printf("\n\n");

	printf("Printing Digits 10 To 1 \n\n");

	ABG_iNum = 10;

	while (ABG_iNum >= 1)
	{
		printf("\t%d\n", ABG_iNum);

		ABG_iNum--;
	}

	return(0);
}