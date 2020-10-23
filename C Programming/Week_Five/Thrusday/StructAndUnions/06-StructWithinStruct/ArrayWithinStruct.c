#include <stdio.h>

struct ABG_MyNumber
{
	int ABG_iNum;
	int ABG_iTable[10];
};

struct ABG_NumTables
{
	struct ABG_MyNumber ABG_First;
	struct ABG_MyNumber ABG_Second;
	struct ABG_MyNumber ABG_Third;
};

int main(void)
{
	unsigned int ABG_uiLoopCounter;
	struct ABG_NumTables ABG_stTables;

	ABG_stTables.ABG_First.ABG_iNum = 12;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_stTables.ABG_First.ABG_iTable[ABG_uiLoopCounter] = ABG_stTables.ABG_First.ABG_iNum * (ABG_uiLoopCounter + 1);

	printf("\n\n");
	printf("Table Of %d :\n\n", ABG_stTables.ABG_First.ABG_iNum);
	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("%d * %d = %d\n", ABG_stTables.ABG_First.ABG_iNum, (ABG_uiLoopCounter + 1), ABG_stTables.ABG_First.ABG_iTable[ABG_uiLoopCounter]);

	ABG_stTables.ABG_Second.ABG_iNum = 17;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_stTables.ABG_Second.ABG_iTable[ABG_uiLoopCounter] = ABG_stTables.ABG_Second.ABG_iNum * (ABG_uiLoopCounter + 1);

	printf("\n\n");
	printf("Table Of %d :\n\n", ABG_stTables.ABG_Second.ABG_iNum);
	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("%d * %d = %d\n", ABG_stTables.ABG_Second.ABG_iNum, (ABG_uiLoopCounter + 1), ABG_stTables.ABG_Second.ABG_iTable[ABG_uiLoopCounter]);

	ABG_stTables.ABG_Third.ABG_iNum = 28;

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		ABG_stTables.ABG_Third.ABG_iTable[ABG_uiLoopCounter] = ABG_stTables.ABG_Third.ABG_iNum * (ABG_uiLoopCounter + 1);

	printf("\n\n");
	printf("Table Of %d :\n\n", ABG_stTables.ABG_Third.ABG_iNum);
	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < 10; ABG_uiLoopCounter++)
		printf("%d * %d = %d\n", ABG_stTables.ABG_Third.ABG_iNum, (ABG_uiLoopCounter + 1), ABG_stTables.ABG_Third.ABG_iTable[ABG_uiLoopCounter]);

   return(0);
}