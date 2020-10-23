#include <stdio.h>

int main(void)
{
	
	int ABG_iValue, ABG_iNum, ABG_iLoopIterator;
	
	printf("\n\n");
	printf("Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &ABG_iValue);
	printf("How Many Digits Do You Want To Print From %d Onwards ? : ", ABG_iValue);
	scanf("%d", &ABG_iNum);
	printf("Printing Digits %d to %d : \n\n", ABG_iValue, (ABG_iValue + ABG_iNum));
	
	ABG_iLoopIterator = ABG_iValue;
	
	while (ABG_iLoopIterator <= (ABG_iValue + ABG_iNum))
	{
		printf("\t%d\n", ABG_iLoopIterator);
		ABG_iLoopIterator++;
	}
	
	printf("\n\n");
	return(0);
}