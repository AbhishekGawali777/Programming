#include <stdio.h>

int main(int argc, char* argv[])
{
	int ABG_iNum = 0;

	//scanf("\nPlease Enter Value For ABG_iNum :%d\t", &ABG_iNum);
	printf("\nPlease Enter Value For iNum:\t");

	scanf("%d", &ABG_iNum);

	if(ABG_iNum < 0)
	{ 
		if (ABG_iNum == 0)
		{
			printf("iNum is zero\n");
		}

		printf("Negative value Of iNum = %d\n", ABG_iNum);
	}
	else if (ABG_iNum > 0)
	{
		printf("Positive Value Of iNum = %d\n", ABG_iNum);
	}
	else
	{
		printf("iNum is zero = %d", ABG_iNum);
	}

	return(0);
}