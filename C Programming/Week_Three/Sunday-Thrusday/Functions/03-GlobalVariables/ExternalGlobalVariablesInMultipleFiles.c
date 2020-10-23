#include <stdio.h>

int ABG_igCount;

int main(void)
{
	void ABG_ChangeCount(void);
	void ABG_ChangeCountOne(void);
	void ABG_ChangeCountTwo(void);

	printf("\n\n");

	ABG_ChangeCount();
	ABG_ChangeCountOne();
	ABG_ChangeCountTwo();

	return(0);
}

void ABG_ChangeCount(void)
{
	ABG_igCount = ABG_igCount + 21;
	printf("Global Count  = %d\n", ABG_igCount);
}