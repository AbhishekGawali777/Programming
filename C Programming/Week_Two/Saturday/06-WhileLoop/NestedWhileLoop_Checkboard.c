#include <stdio.h>
int main(void)
{
	int ABG_iNum1, ABG_iNum2, ABG_iNum3;
	
	printf("\n\n");

	ABG_iNum1 = 0;

	while (ABG_iNum1 < 64)
	{
		ABG_iNum2 = 0;
		while (ABG_iNum2 < 64)
		{
			ABG_iNum3 = ((ABG_iNum1 & 0x8) == 0) ^ ((ABG_iNum2 & 0x8) == 0);
			if (ABG_iNum3 == 0)
				printf(" ");
			if (ABG_iNum3 == 1)
				printf("* ");
			ABG_iNum2++;
		}
		printf("\n\n");
	
		ABG_iNum1++;
	}

	return(0);
}