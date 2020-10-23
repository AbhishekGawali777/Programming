#include <stdio.h>

struct ABG_MyData
{
	int ABG_iNum;
	char ABG_cCh;
	float ABG_fNum;
	double ABG_dNum;
};

int main(void)
{
	struct ABG_MyData ABG_lObject;
	printf("\n\n");

	printf("Enter Integer Value For Data Member 'ABG_iNum' Of 'struct ABG_MyData' :\t");
	scanf("%d", &ABG_lObject.ABG_iNum);

	printf("\nEnter Character Value For Data Member 'ABG_cCh' Of 'struct ABG_MyData' :\t");
	//scanf("%c", &ABG_lObject.ABG_cCh);
	ABG_lObject.ABG_cCh = getche();

	printf("\nEnter Floating-Point Value For Data Member 'ABG_fNum' Of 'struct ABG_MyData' :\t");
	scanf("%f", &ABG_lObject.ABG_fNum);

	printf("\nEnter 'Double' Value For Data Member 'ABG_dNum' Of 'struct ABG_MyData' :\t");
	scanf("%lf", &ABG_lObject.ABG_dNum);

	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyData' Are :\n\n");
	printf("ABG_iNum = %d\n", ABG_lObject.ABG_iNum);
	printf("ABG_cCh = %c\n", ABG_lObject.ABG_cCh);
	printf("ABG_fNum = %f\n", ABG_lObject.ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_lObject.ABG_dNum);

	return(0);
}