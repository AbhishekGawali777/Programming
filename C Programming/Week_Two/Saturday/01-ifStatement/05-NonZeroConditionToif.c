#include <stdio.h>

int main(void)
{
	int ABG_iNum;

	printf("\n\n");

	ABG_iNum = 11;

	if(ABG_iNum)
	{ 
		printf("if-block1 : 'ABG_iNum' Exists And Has Value = %d.!!!\n\n", ABG_iNum);
	}

	ABG_iNum = -11;

	if (ABG_iNum)
	{
		printf("if-block2 : 'ABG_iNum' Exists And Has Value = %d.!!!\n\n", ABG_iNum);
	}

	ABG_iNum = 0;

	if (ABG_iNum)
	{
		printf("if-block3 : 'ABG_iNum' Exists And Has Value = %d.!!!\n\n", ABG_iNum);
	}

	printf("All Three if-Statements Are Done.!!!\n\n");

	return(0);
}