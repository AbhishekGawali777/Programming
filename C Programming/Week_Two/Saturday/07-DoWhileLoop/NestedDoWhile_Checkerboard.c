#include <stdio.h>

int main(void)
{

	int ABG_iNum1, ABG_iNum2, ABG_iResult;

	printf("\n\n");

	ABG_iNum1 = 0;

	do
	{
		ABG_iNum2 = 0;

		do
		{
			ABG_iResult = ((ABG_iNum1 & 0x8) == 0) ^ ((ABG_iNum2 & 0x8) == 0);

			if (ABG_iResult == 0)
				printf(" ");
			if (ABG_iResult == 1)
				printf(" * ");

			ABG_iNum2++;

		} while (ABG_iNum2 < 64);
		printf("\n\n");

		ABG_iNum1++;

	} while (ABG_iNum1 < 64);


	return(0);
}