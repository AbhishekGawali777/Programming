#include <stdio.h>
int main(void)
{
	
	int ABG_iNum1, ABG_iNum2, ABG_iNum3;
	
	printf("\n\n");
	
	ABG_iNum1 = 1;
	
	while (ABG_iNum1 <= 10)
	{
		printf("i = %d\n", ABG_iNum1);
		printf("--------\n\n");
		
		ABG_iNum2 = 1;
		
		while (ABG_iNum2 <= 5)
		{
			printf("\tj = %d\n", ABG_iNum2);
			printf("\t--------\n\n");
		
			ABG_iNum3 = 1;
			
			while (ABG_iNum3 <= 3)
			{
				printf("\t\tk = %d\n", ABG_iNum3);
				ABG_iNum3++;
			}
			
			printf("\n\n");
			
			ABG_iNum2++;
		}
		printf("\n\n");

		ABG_iNum1++;
	}
	return(0);
}