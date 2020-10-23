#include <stdio.h>

int main(void)
{
	float ABG_fNum1;
	float ABG_fNum2 = 3.971f; 
	
	printf("\n\n");
	printf("Printing Numbers %f to %f : \n\n", ABG_fNum2, (ABG_fNum2 * 10.0f));
	for (ABG_fNum1 = ABG_fNum2; ABG_fNum1 <= (ABG_fNum2 * 10.0f); ABG_fNum1 = ABG_fNum1 + ABG_fNum2)
	{
		printf("\t%f\n", ABG_fNum1);
	}
	printf("\n\n");
	return(0);
}