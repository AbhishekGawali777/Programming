#include <stdio.h>

int main(void)
{

	int ABG_iNum, ABG_iValue, ABG_LoopCounter;

	printf("\n\n");

	printf("Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &ABG_iNum);
	
	printf("How Many Digits Do You Want To Print From %d Onwards ? : ", ABG_iNum);
	scanf("%d", &ABG_iValue);
	
	printf("Printing Digits %d to %d : \n\n", ABG_iNum, (ABG_iNum + ABG_iValue));
	
	for (ABG_LoopCounter = ABG_iNum; ABG_LoopCounter <= (ABG_iNum + ABG_iValue); ABG_LoopCounter++)
	{
		printf("\t%d\n", ABG_LoopCounter);
	}
	
	printf("\n\n");
	
	return(0);
}