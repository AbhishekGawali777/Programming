#include <stdio.h>

int main(void)
{
	int ABG_iNum1, ABG_iNum2, ABG_iNum3, ABG_iNum4;
	
	char ABG_cCh_Result1, ABG_cCh_Result2;
	int  ABG_iResult1, ABG_iResult2;


	printf("\n\n");
	ABG_iNum1 = 5;
	ABG_iNum2 = 10;

	ABG_cCh_Result1 = (ABG_iNum1 > ABG_iNum2) ? 'A' : 'B';

	ABG_iResult1 = (ABG_iNum1 > ABG_iNum2) ? ABG_iNum1 : ABG_iNum2;

	printf("Ternary operator Answer 1 ------- %c and %d.\n\n", ABG_cCh_Result1, ABG_iResult1);

	ABG_iNum3 = 65;
	ABG_iNum4 = 65;

	ABG_cCh_Result2 = (ABG_iNum3 != ABG_iNum4) ? 'P' : 'Q';

	ABG_iResult2 = (ABG_iNum3 > ABG_iNum4) ? ABG_iNum3 : ABG_iNum4;

	printf("Ternary operator Answer 2 ------- %c and %d.\n\n", ABG_cCh_Result2, ABG_iResult2);


	return(0);
}