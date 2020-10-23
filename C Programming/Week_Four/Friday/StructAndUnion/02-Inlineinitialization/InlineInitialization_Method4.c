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
	struct ABG_MyData ABG_DataOne = { 77, 'A', 21.07f, 233.7017 };
	struct ABG_MyData ABG_DataTwo = { 50, 'B', 48.12f, 43.68 };
	struct ABG_MyData ABG_DataThree = { 80, 'H', 37.49f, 613.521 };
	struct ABG_MyData ABG_DataFour = {48, 'I', 25.52f, 14.13592};

	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyData ABG_DataOne' Are :\n\n");
	printf("ABG_iNum = %d\n", ABG_DataOne.ABG_iNum);
	printf("ABG_icCh = %c\n", ABG_DataOne.ABG_cCh);
	printf("ABG_fNum = %f\n", ABG_DataOne.ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_DataOne.ABG_dNum);

	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyData ABG_DataTwo' Are :\n\n");
	printf("ABG_iNum = %d\n", ABG_DataTwo.ABG_iNum);
	printf("ABG_icCh = %c\n", ABG_DataTwo.ABG_cCh);
	printf("ABG_fNum = %f\n", ABG_DataTwo.ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_DataTwo.ABG_dNum);
	
	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyData ABG_DataThree' Are :\n\n");
	printf("ABG_iNum = %d\n", ABG_DataThree.ABG_iNum);
	printf("ABG_icCh = %c\n", ABG_DataThree.ABG_cCh);
	printf("ABG_fNum = %f\n", ABG_DataThree.ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_DataThree.ABG_dNum);
	
	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyData ABG_DataFour' Are :\n\n");
	printf("ABG_iNum = %d\n", ABG_DataFour.ABG_iNum);
	printf("ABG_icCh = %c\n", ABG_DataFour.ABG_cCh);
	printf("ABG_fNum = %f\n", ABG_DataFour.ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_DataFour.ABG_dNum);
	
	return(0);
}