#include <stdio.h>

int main(void)
{
	unsigned int ABG_uiMonth;

	printf("\n\n");

	printf("Enter Number Of Month (1 To 12) : \t");
	scanf("%d", &ABG_uiMonth);

	printf("\n\n");

	switch (ABG_uiMonth)
	{
	case 1:
		printf("Month Number %d Is JANUARY.!!!\n\n", ABG_uiMonth);
		break;

	case 2:
		printf("Month Number %d Is FEBRUARY.!!!\n\n", ABG_uiMonth);
		break;

	case 3:
		printf("Month Number %d Is MARCH.!!!\n\n", ABG_uiMonth);
		break;

	case 4:
		printf("Month Number %d Is APRIL.!!!\n\n", ABG_uiMonth);
		break;

	case 5:
		printf("Month Number %d Is MAY.!!!\n\n", ABG_uiMonth);
		break;

	case 6:
		printf("Month Number %d Is JUNE.!!!\n\n", ABG_uiMonth);
		break;

	case 7:
		printf("Month Number %d Is JULY.!!!\n\n", ABG_uiMonth);
		break;

	case 8:
		printf("Month Number %d Is AUGUST.!!!\n\n", ABG_uiMonth);
		break;

	case 9:
		printf("Month Number %d Is SEPTEMBER.!!!\n\n", ABG_uiMonth);
		break;

	case 10:
		printf("Month Number %d Is OCTOBER.!!!\n\n", ABG_uiMonth);
		break;

	case 11:
		printf("Month Number %d Is NOVEMBER.!!!\n\n", ABG_uiMonth);
		break;

	case 12:
		printf("Month Number %d Is DECEMBER.!!!\n\n", ABG_uiMonth);
		break;

	default:
		printf("Invalid Month Number %d Entered.!!! Please Try Again...!!!\n\n", ABG_uiMonth);
	}

	printf("Switch Case Block Complete.!!!\n\n");

	return(0);
}