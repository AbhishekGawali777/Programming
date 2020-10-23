#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	unsigned int ABG_iNum;

	void ABG_Recursive(unsigned int);

	printf("\n\n");
	printf("Enter Any Number : \t");
	scanf("%u", &ABG_iNum);

	printf("\n\n");
	printf("Output Of Recursive Function :\n\n");

	ABG_Recursive(ABG_iNum);

	printf("\n\n");
	return(0);
}

void ABG_Recursive(unsigned int ABG_iNum)
{
	printf("ABG_iNum = %d\n", ABG_iNum);

	if (ABG_iNum > 0)
		ABG_Recursive(ABG_iNum - 1);
}