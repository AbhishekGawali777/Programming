#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	void MyAddition(int, int);


	int ABG_iNum1, ABG_iNum2;

	printf("\n\nEnter First Number :\t");
	scanf("%d", &ABG_iNum1);

	printf("\n\nEnter Second Number :\t");
	scanf("%d", &ABG_iNum2);

    MyAddition(ABG_iNum1, ABG_iNum2);

	return(0);
}
void MyAddition(int ABG_iNum1, int ABG_iNum2)
{
	int ABG_iSum;

	
	ABG_iSum = ABG_iNum1 + ABG_iNum2;

	printf("\n\nSum Of Numbers Is :\t%d\n\n", ABG_iSum);

}