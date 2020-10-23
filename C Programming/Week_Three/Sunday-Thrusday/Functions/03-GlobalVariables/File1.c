#include <stdio.h>

extern int ABG_igCount;

void ABG_ChangeCountOne(void)
{
	ABG_igCount = ABG_igCount + 99;
	printf("ABG_ChangeCountOne() : Value Of ABG_igCount In File File1.c Is %d\n", ABG_igCount);
}