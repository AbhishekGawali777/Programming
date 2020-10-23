#include <stdio.h>

struct ABG_MyData
{
	int ABG_iData;
	char ABG_cData;
	float ABG_fData;
	double ABG_dData;
};

int main(void)
{
	struct ABG_MyData ABG_stMyData;

	ABG_stMyData.ABG_iData = 56;
	ABG_stMyData.ABG_cData = 'A';
	ABG_stMyData.ABG_fData = 69.23f;
	ABG_stMyData.ABG_dData = 256.983425;

	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyData' Are : \n\n");
	printf("ABG_iData = %d\n", ABG_stMyData.ABG_iData);
	printf("ABG_cData = %c\n", ABG_stMyData.ABG_cData);
	printf("ABG_fData = %f\n", ABG_stMyData.ABG_fData);
	printf("ABG_dData = %lf\n", ABG_stMyData.ABG_dData);

	printf("\n\n");
	printf("Address Of Data Members Of 'struct ABG_MyData' Are : \n\n");
	printf("'ABG_iData' Occupies Address From %p\n", &ABG_stMyData.ABG_iData);
	printf("'ABG_cData' Occupies Address From %p\n", &ABG_stMyData.ABG_cData);
	printf("'ABG_fData' Occupies Address From %p\n", &ABG_stMyData.ABG_fData);
	printf("'ABG_dData' Occupies Address  %p\n\n", &ABG_stMyData.ABG_dData);

	printf("Starting Address Of 'struct ABG_MyData' Variable ABG_stMyData = %p\n\n", &ABG_stMyData);

	return(0);
}