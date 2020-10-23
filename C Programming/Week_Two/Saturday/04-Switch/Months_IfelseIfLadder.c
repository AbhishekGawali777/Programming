#include <stdio.h>

int main(void)
{
	unsigned int ABG_uiMonth;

	printf("\n\n");

	printf("Enter Number Of Month : \t");
	scanf("%u", &ABG_uiMonth);

	printf("\n\n");

	if (1 == ABG_uiMonth)
		printf("Month Number %u Is JANUARY\n\n", ABG_uiMonth);
	else if (2 == ABG_uiMonth)
		printf("Month Number %u Is FEBRUARY\n\n", ABG_uiMonth);
	else if (3 == ABG_uiMonth)
		printf("Month Number %u Is MARCH\n\n", ABG_uiMonth);
	else if (4 == ABG_uiMonth)
		printf("Month Number %u Is APRIL\n\n", ABG_uiMonth);
	else if (5 == ABG_uiMonth)
		printf("Month Number %u Is MAY\n\n", ABG_uiMonth);
	else if (6 == ABG_uiMonth)
		printf("Month Number %u Is JUNE\n\n", ABG_uiMonth);
	else if (7 == ABG_uiMonth)
		printf("Month Number %u Is JULY\n\n", ABG_uiMonth);
	else if (8 == ABG_uiMonth)
		printf("Month Number %u Is AUGUST\n\n", ABG_uiMonth);
	else if (9 == ABG_uiMonth)
		printf("Month Number %u Is SEPTEMBER\n\n", ABG_uiMonth);
	else if (10 == ABG_uiMonth)
		printf("Month Number %u Is OCTOBER\n\n", ABG_uiMonth);
	else if (11 == ABG_uiMonth)
		printf("Month Number %u Is NOVEMBER\n\n", ABG_uiMonth);
	else if (12 == ABG_uiMonth)
		printf("Month Number %u Is DECEMBER\n\n", ABG_uiMonth);
	else
		printf("Invalid Month Number %u Entered.!!! Please Try Again..!!!\n\n", ABG_uiMonth);

	printf("If - Else If - Else Ladder Completeed.!!!\n\n");

	return(0);
}