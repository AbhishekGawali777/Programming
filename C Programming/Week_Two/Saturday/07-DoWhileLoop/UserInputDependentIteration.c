#include <stdio.h>

int main(void)
{

	int ABG_iNum1, ABG_iNum2, ABG_iLoopCounter;

	printf("\n\n");
	printf("Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &ABG_iNum1);
	printf("How Many Digits Do You Want To Print From %d Onwards ? : ", ABG_iNum1);
	scanf("%d", &ABG_iNum2);
	printf("Printing Digits %d to %d : \n\n", ABG_iNum1, (ABG_iNum1 + ABG_iNum2));
	ABG_iLoopCounter = ABG_iNum1;
	do
	{
		printf("\t%d\n", ABG_iLoopCounter);
		ABG_iLoopCounter++;
	} while (ABG_iLoopCounter <= (ABG_iNum1 + ABG_iNum2));

	printf("\n\n");
	
	return(0);
}