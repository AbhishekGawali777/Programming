#include <stdio.h>

int main(int argc, char* argv[])
{
	int ABG_iNum1;
	int ABG_iNum2;
	int ABG_iNum3;
	int ABG_iResult;

	printf("\n\n");
	printf("Enter First Integer :\t");
	scanf("%d", &ABG_iNum1);

	printf("\n\n");
	printf("Enter Second Integer :\t");
	scanf("%d", &ABG_iNum2);

	printf("\n\n");
	printf("Enter Third Integer :\t");
	scanf("%d", &ABG_iNum3);

	printf("\n\n");
	printf("If Answer Is = 0, It's 'FALSE'.\n");
	printf("If Answer Is = 1, It's 'TRUE'.\n\n");

	ABG_iResult = (ABG_iNum1 <= ABG_iNum2) && (ABG_iNum2 != ABG_iNum3);
	printf("LOGICAL AND	(&&) : Answer Is True (1) If And Only If Both Conditions Are True. The Answer Is False (0), If Any One Or Both Conditions Are False\n\n");
	printf("ABG_iNum1 = %d Is Less Than Or Equal To ABG_iNum2 = %d 'AND' ABG_iNum2 = %d Is NOT Equal To ABG_iNum3 = %d\t Answer  = %d\n\n", ABG_iNum1, ABG_iNum2, ABG_iNum2, ABG_iNum3, ABG_iResult);

	ABG_iResult = (ABG_iNum2 >= ABG_iNum1) || (ABG_iNum1 == ABG_iNum3);
	printf("LOGICAL OR (||) : Answer Is True (1) If  Both Conditions Are True. The Answer Is False (0), If Both Conditions Are False\n\n");
	printf("ABG_iNum2 = %d Is Greater Than Or Equal To ABG_iNum1 = %d 'OR' ABG_iNum1 = %d Is Equal To ABG_iNum3 = %d\t Answer  = %d\n\n", ABG_iNum2, ABG_iNum1, ABG_iNum1, ABG_iNum3, ABG_iResult);

	ABG_iResult = !ABG_iNum1;
	printf("ABG_iNum1 = %d And Using Logical NOT (!) Operator On A Gives Result = %d\n\n", ABG_iNum1, ABG_iResult);

	ABG_iResult = !ABG_iNum2;
	printf("ABG_iNum2 = %d And Using Logical NOT (!) Operator On B Gives Result = %d\n\n", ABG_iNum2, ABG_iResult);

	ABG_iResult = !ABG_iNum3;
	printf("ABG_iNum3 = %d And Using Logical NOT (!) Operator On C Gives Result = %d\n\n", ABG_iNum3, ABG_iResult);

	ABG_iResult = (!(ABG_iNum1 <= ABG_iNum2) && !(ABG_iNum2 != ABG_iNum3));
	printf("Using Logical NOT (!) On (ABG_iNum1 <= ABG_iNum2) And Also On (ABG_iNum2 != ABG_iNum3) And Then AND-ing Them Afterwards Gives Result  = %d\n\n", ABG_iResult);

	printf("\n\n");

	ABG_iResult = !((ABG_iNum2 >= ABG_iNum1) || (ABG_iNum1 == ABG_iNum3));
	printf("Using Logical NOT (!) On Entire Logical Expression (ABG_iNum2 >= ABG_iNum1) || (ABG_iNum1 == ABG_iNum3) Gives Result = %d\n", ABG_iResult);

	printf("\n\n");

	return(0);
}