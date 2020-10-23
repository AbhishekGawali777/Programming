#include <stdio.h>

int main(void)
{
	int ABG_iNum;

	printf("\n\n");

	printf("Printing Digits 1 to 10 : \n\n");

	ABG_iNum = 1;

	do
	{
		printf("\t%d\n", ABG_iNum);
		ABG_iNum++;
	} while (ABG_iNum <= 10);

	printf("\n\n");

	return(0);
}