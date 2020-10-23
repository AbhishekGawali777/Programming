#include <stdio.h>

int main(void)
{
	//variable declarations
	int ABG_iNum;
	//code
	printf("\n\n");

	printf("Enter Value For 'ABG_iNum' : ");
	scanf("%d", &ABG_iNum);

	if (ABG_iNum < 0) 
	{
		printf("ABG_iNum = %d Is Less Than 0 (NEGATIVE) !!!\n\n", ABG_iNum);
	}
	else 
	{
		if ((ABG_iNum > 0) && (ABG_iNum <= 100))
		{
			printf("ABG_iNum = %d Is Between 0 And 100 !!!\n\n", ABG_iNum);
		}
		else 
		{
			if ((ABG_iNum > 100) && (ABG_iNum <= 200))
			{
				printf("ABG_iNum = %d Is Between 100 And 200 !!!\n\n", ABG_iNum);
			}
			else 
			{
				if ((ABG_iNum > 200) && (ABG_iNum <= 300)) 
				{
					printf("ABG_iNum = %d Is Between 200 And 300 !!!\n\n", ABG_iNum);
				}
				else 
				{
					if ((ABG_iNum > 300) && (ABG_iNum <= 400)) 
					{
						printf("ABG_iNum = %d Is Between 300 And 400 !!!\n\n", ABG_iNum);
					}
					else 
					{
						if ((ABG_iNum > 400) && (ABG_iNum <= 500)) 
						{
							printf("ABG_iNum = %d Is Between 400 And 500 !!!\n\n",
								ABG_iNum);
						}
						else 
						{
							printf("ABG_iNum = %d Is Greater Than 500 !!!\n\n", ABG_iNum);
						}
					}
				}
			}
		}
	}
}