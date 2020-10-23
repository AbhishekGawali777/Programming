#include <stdio.h>

extern int ABG_igCount;

void ABG_ChangeCountTwo(void)
{
	ABG_igCount = ABG_igCount + 128;
	printf("ABG_ChangeCountTwo() : Value Of ABG_igCount In File File1.c Is %d\n", ABG_igCount);
}