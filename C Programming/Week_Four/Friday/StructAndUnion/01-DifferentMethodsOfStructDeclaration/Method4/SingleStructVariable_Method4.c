#include <stdio.h>

struct ABG_MyData
{
	int ABG_iNum;
	float ABG_fNum;
	double ABG_dNum;
};


int main(void)
{
	struct ABG_MyData ABG_sData;

	int ABG_iIntSize;
	int ABG_iFloatSize;
	int ABG_iDoubleSize;
	int ABG_MyDataStructSize;

	ABG_sData.ABG_iNum = 185;
	ABG_sData.ABG_fNum = 268.25f;
	ABG_sData.ABG_dNum = 2356.2656;

	printf("Data Members Of 'Struct ABG_MyData' Are : \n\n");
	printf("ABG_iNum = %d\n", ABG_sData.ABG_iNum);
	printf("ABG_fNum = %f\n", ABG_sData.ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_sData.ABG_dNum);

	ABG_iIntSize = sizeof(ABG_sData.ABG_iNum);
	ABG_iFloatSize = sizeof(ABG_sData.ABG_fNum);
	ABG_iDoubleSize = sizeof(ABG_sData.ABG_dNum);

	printf("\n\n");
	printf("'SIZES OF DATA MEMBERS In' struct ABG_MyData:\n\n");
	printf("Size Of ABG_iIntSize = %d\n", ABG_iIntSize);
	printf("Size Of ABG_iFloatSize = %d\n", ABG_iFloatSize);
	printf("Size Of ABG_iDoubleSize = %d\n", ABG_iDoubleSize);

	ABG_MyDataStructSize = sizeof(struct ABG_MyData);

	printf("Size Of ABG_MyDataStructSize = %d\n", ABG_MyDataStructSize);


	return(0);
}