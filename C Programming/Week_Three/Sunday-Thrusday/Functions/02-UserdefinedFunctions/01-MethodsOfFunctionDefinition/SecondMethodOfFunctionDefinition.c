#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	int MyAddition();
	int ABG_iSum;

	ABG_iSum = MyAddition();

	printf("\n\nSum Of Numbers Is :\t%d\n\n", ABG_iSum);

	return(0);
}

int MyAddition(void)
{
	int ABG_iNum1, ABG_iNum2, ABG_iSum;

	printf("\n\nEnter First Number :\t");
	scanf("%d", &ABG_iNum1);

	printf("\n\nEnter Second Number :\t");
	scanf("%d", &ABG_iNum2);

	ABG_iSum = ABG_iNum1 + ABG_iNum2;

	return ABG_iSum;
}