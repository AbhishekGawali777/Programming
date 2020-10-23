#include <stdio.h>

struct ABG_MyNumber
{
	int ABG_iNum;
	int ABG_iTable[10];
};

struct ABG_NumTables
{
	struct ABG_MyNumber ABG_stMyNumber;
};

int main(void)
{
	struct ABG_NumTables ABG_stNumTables[10];
	unsigned int uiLoopCounter1, uiLoopCounter2;

	for (uiLoopCounter1 = 0; uiLoopCounter1 < 10; uiLoopCounter1++)
	{
		ABG_stNumTables[uiLoopCounter1].ABG_stMyNumber.ABG_iNum = (uiLoopCounter1 + 1);
	}

	for (uiLoopCounter1 = 0; uiLoopCounter1 < 10; uiLoopCounter1++)
	{
		printf("\n\n");
		printf("Table Of %d :\n\n", ABG_stNumTables[uiLoopCounter1].ABG_stMyNumber.ABG_iNum);

		for (uiLoopCounter2 = 0; uiLoopCounter2 < 10; uiLoopCounter2++)
		{
			ABG_stNumTables[uiLoopCounter1].ABG_stMyNumber.ABG_iTable[uiLoopCounter2] =
				ABG_stNumTables[uiLoopCounter1].ABG_stMyNumber.ABG_iNum * (uiLoopCounter2 + 1);

			printf("%d * %d = %d\n", ABG_stNumTables[uiLoopCounter1].ABG_stMyNumber.ABG_iNum, (uiLoopCounter2 + 1), 
				ABG_stNumTables[uiLoopCounter1].ABG_stMyNumber.ABG_iTable[uiLoopCounter2]);
		}
	}


	return(0);
}