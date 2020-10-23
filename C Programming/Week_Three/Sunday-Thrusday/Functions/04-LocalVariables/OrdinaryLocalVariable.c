#include <stdio.h>

int main(void)
{
	int ABG_iNum = 5;

	void ABG_ChangeCount(void);

	printf("\n\n");
	printf("A = %d\n\n", ABG_iNum);

	ABG_ChangeCount();
	ABG_ChangeCount();
	ABG_ChangeCount();

	return(0);
}

void ABG_ChangeCount(void)
{
	int ABG_iLocalCount = 0;

	ABG_iLocalCount = ABG_iLocalCount + 10;
	printf("Local Count = %d\n\n", ABG_iLocalCount);
}