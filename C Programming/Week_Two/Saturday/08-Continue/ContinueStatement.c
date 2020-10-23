#include <stdio.h>

int main(void)
{
	int ABG_iNum;

	printf("\n\n");

	printf("\t\tPrinting Even Numbers From 0 To 80\n\n");

	for (ABG_iNum = 0; ABG_iNum <= 80; ABG_iNum++)
	{
		if ((ABG_iNum % 2) == 0)
			printf("\t%d\n", ABG_iNum);
		else
			continue;
	}

	return(0);
}