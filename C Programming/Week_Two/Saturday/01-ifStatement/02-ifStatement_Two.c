#include <stdio.h>

int main(void)
{
	unsigned int ABG_uiAge;

	printf("\n\n");

	printf("Enter Your Age:\t");
	scanf("%u", &ABG_uiAge);

	if (ABG_uiAge >= 18)
		printf("You Are Eligible For Voting..!!!\n\n");

	return(0);
}