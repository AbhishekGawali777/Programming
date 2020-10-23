#include <stdio.h>

int ABG_igCount;

int main(void)
{
	void ABG_ChangeCountOne(void);
	void ABG_ChangeCountTwo(void);
	void ABG_ChangeCountThree(void);

	printf("\n");

	printf("main() : Value of ABG_igCount = %d\n", ABG_igCount);

	ABG_ChangeCountOne();
	ABG_ChangeCountTwo();
	ABG_ChangeCountThree();

	printf("\n");
	return(0);
}

void ABG_ChangeCountOne(void)
{
	ABG_igCount = 100;
	printf("ABG_ChangeCountOne() : Value of ABG_igCount = %d\n", ABG_igCount);
}

void ABG_ChangeCountTwo(void)
{
	ABG_igCount = ABG_igCount + 50;
	printf("ABG_ChangeCountTwo() : Value of ABG_igCount = %d\n", ABG_igCount);
}

void ABG_ChangeCountThree(void)
{
	ABG_igCount = ABG_igCount + 550;
	printf("ABG_ChangeCountThree() : Value of ABG_igCount = %d\n", ABG_igCount);
}