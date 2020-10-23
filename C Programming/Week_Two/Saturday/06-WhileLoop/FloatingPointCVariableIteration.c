#include <stdio.h>

int main(void)
{
	float ABG_fNum1;
	float ABG_fNum2 = 3.45f;

	printf("\n\n");

	printf("Printing Number %f To %f :\n\n", ABG_fNum2, (ABG_fNum2 * 10.0f));

	ABG_fNum1 = ABG_fNum2;

	while (ABG_fNum1 <= ABG_fNum2 * 10.0f)
	{
		printf("\t%f\n", ABG_fNum1);
		ABG_fNum1 = ABG_fNum1 + ABG_fNum2;
	}

	printf("\n\n");

	return(0);
}