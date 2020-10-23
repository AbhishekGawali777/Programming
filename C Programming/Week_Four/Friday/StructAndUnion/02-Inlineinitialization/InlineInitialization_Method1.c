#include <stdio.h>

struct ABG_MyData
{
	int ABG_iNum;
	char ABG_cCh;
	float ABG_fNum;
	double ABG_dNum;
}ABG_sData = {256, 'A', 25.40f, 328.147};

int main(void)
{

	printf("\n\n");
	printf("Data Members Of 'Struct ABG_MyData' Are : \n\n");
	printf("ABG_iNum = %d\n", ABG_sData.ABG_iNum);
	printf("ABG_cCh = %c\n", ABG_sData.ABG_cCh);
	printf("ABG_fNum = %f\n", ABG_sData.ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_sData.ABG_dNum);


	return(0);
}