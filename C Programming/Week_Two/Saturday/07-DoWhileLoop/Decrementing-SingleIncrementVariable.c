#include <stdio.h>

int main(void)
{
	int ABG_iNum;
	
	printf("\n\n");
	printf("Printing Digits 10 to 1 : \n\n");
	
	ABG_iNum = 10;
	
	do
	{
		printf("\t%d\n", ABG_iNum);
		ABG_iNum--;
	} while (ABG_iNum >= 1);
	
	printf("\n\n");
	
	return(0);
}