#include <stdio.h>

int main(void)
{
	unsigned int ABG_iAge;

	printf("\n\n");
	printf("Enter Your Age : \t");
	scanf("%u", &ABG_iAge);

	if (ABG_iAge >= 18)
		printf("You Are Eligible For Voting.!!!\n\n");
	else
		printf("You Are Not Eligible For Voting.!!!\n\n");
	
	return(0);
}