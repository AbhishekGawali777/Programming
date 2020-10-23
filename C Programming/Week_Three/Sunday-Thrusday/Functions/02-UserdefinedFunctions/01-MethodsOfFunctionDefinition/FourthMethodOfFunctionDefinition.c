#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	int MyAddition(int, int);


	int ABG_iNum1, ABG_iNum2, ABG_iSum;

	printf("\n\nEnter First Number :\t");
	scanf("%d", &ABG_iNum1);

	printf("\n\nEnter Second Number :\t");
	scanf("%d", &ABG_iNum2);

	ABG_iSum = MyAddition(ABG_iNum1, ABG_iNum2);

	printf("\n\nSum Of Numbers %d And %d Is :\t%d\n\n",ABG_iNum1, ABG_iNum2, ABG_iSum);

	return(0);
}
int MyAddition(int ABG_iNum1, int ABG_iNum2)
{
	int ABG_iSum;

	ABG_iSum = ABG_iNum1 + ABG_iNum2;

	return(ABG_iSum);
}