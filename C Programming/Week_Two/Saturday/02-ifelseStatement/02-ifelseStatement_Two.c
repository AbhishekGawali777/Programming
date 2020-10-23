#include <stdio.h>

int main(void)
{
	//variable declarations
	int ABG_iAge;
	//code
	printf("\n\n");
	
	printf("Enter Age : ");
	scanf("%d", &ABG_iAge);
	
	printf("\n\n");

	if (ABG_iAge >= 18)
	{
		printf("Entering if-block...\n\n");
		printf("You Are Eligible For Voting !!!\n\n");
	}
	else
	{
		printf("Entering else-block...\n\n");
		printf("You Are NOT Eligible For Voting !!!\n\n");
	}
	printf("Bye !!!\n\n");
	return(0);
}