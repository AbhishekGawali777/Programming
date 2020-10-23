#include <stdio.h>

int main(void)
{
	void ABG_ChangeCount(void);

	extern int ABG_igCount;

	printf("\n");
	printf("Value Of global_count before ABG_ChangeCount() = %d\n", ABG_igCount);

	ABG_ChangeCount();

	printf("Value Of global_count after ABG_ChangeCount() = %d\n", ABG_igCount);
	printf("\n");

	return(0);
}

int ABG_igCount;

void ABG_ChangeCount(void)
{

	ABG_igCount = 21;
	printf("Value Of global_count in ABG_ChangeCount() = %d\n", ABG_igCount);
}