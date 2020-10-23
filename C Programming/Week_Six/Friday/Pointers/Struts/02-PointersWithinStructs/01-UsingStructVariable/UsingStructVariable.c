#include <stdio.h>

struct ABG_MyData
{
	int* ABG_iPtr;
	int ABG_iNum;

	float* ABG_fPtr;
	float ABG_fNum;

	double* ABG_dPtr;
	double ABG_dNum;
};

int main(void)
{
	// Variable Declarations

	struct ABG_MyData ABG_stData;

	// Code

	ABG_stData.ABG_iNum = 12;
	ABG_stData.ABG_iPtr = &ABG_stData.ABG_iNum;

	ABG_stData.ABG_fNum = 96.47f;
	ABG_stData.ABG_fPtr = &ABG_stData.ABG_fNum;

	ABG_stData.ABG_dNum = 8972.17852;
	ABG_stData.ABG_dPtr = &ABG_stData.ABG_dNum;

	printf("\n\n");
	printf("ABG_iNum = %d\n", *(ABG_stData.ABG_iPtr));
	printf("Address Of ABG_iNum = %p\n", ABG_stData.ABG_iPtr);

	printf("\n\n");
	printf("ABG_fNum = %f\n", *(ABG_stData.ABG_fPtr));
	printf("Address Of ABG_fNum = %p\n", ABG_stData.ABG_fPtr);

	printf("\n\n");
	printf("ABG_dNum = %lf\n", *(ABG_stData.ABG_dPtr));
	printf("Address Of ABG_dNum = %p\n", ABG_stData.ABG_dPtr);

	return(0);
}	