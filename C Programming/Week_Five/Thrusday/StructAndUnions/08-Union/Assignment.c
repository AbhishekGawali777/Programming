#include <stdio.h>

// union Declaration

union ABG_MyUnion
{
	int ABG_iData;
	char ABG_cData;
	float ABG_fData;
	double ABG_dData;
};

int main(void)
{
	// Variable Declaration
	union ABG_MyUnion ABG_union1, ABG_union2;

	/*****	ABG_union1	*****/

	printf("\n\n");
	printf("Members Of Union 'ABG_union1' Are: \n\n");

	ABG_union1.ABG_iData = 67;
	ABG_union1.ABG_cData = 'A';
	ABG_union1.ABG_fData = 97.26f;
	ABG_union1.ABG_iData = 512.671946;

	printf("ABG_union1.ABG_iData = %d\n", ABG_union1.ABG_iData);
	printf("ABG_union1.ABG_cData = %c\n", ABG_union1.ABG_cData);
	printf("ABG_union1.ABG_fData = %f\n", ABG_union1.ABG_fData);
	printf("ABG_union1.ABG_dData = %lf\n\n\n", ABG_union1.ABG_dData);

	printf("Address Of Members Of ABG_union1 Are :\n\n");

	printf("ABG_union1.ABG_iData = %p\n", &ABG_union1.ABG_iData);
	printf("ABG_union1.ABG_cData = %p\n", &ABG_union1.ABG_cData);
	printf("ABG_union1.ABG_fData = %p\n", &ABG_union1.ABG_fData);
	printf("ABG_union1.ABG_dData = %p\n\n\n", &ABG_union1.ABG_dData);

	printf("ABG_MyUnion ABG_union1 = %p\n\n", &ABG_union1);

	/*****	ABG_union2	*****/

	printf("Members Of Union 'ABG_union2' Are : \n\n");

	ABG_union2.ABG_iData = 33;
	printf("ABG_union2.ABG_iData = %d\n", ABG_union2.ABG_iData);

	ABG_union2.ABG_cData = 'V';
	printf("ABG_union2.ABG_cData = %c\n", ABG_union2.ABG_cData);

	ABG_union2.ABG_fData = 77.56f;
	printf("ABG_union2.ABG_fData = %f\n", ABG_union2.ABG_fData);

	ABG_union2.ABG_dData = 33;
	printf("ABG_union2.ABG_dData = %lf\n", ABG_union2.ABG_dData);

	printf("Address Of Members Of ABG_union2 Are :\n\n");

	printf("ABG_union2.ABG_iData = %p\n", &ABG_union2.ABG_iData);
	printf("ABG_union2.ABG_cData = %p\n", &ABG_union2.ABG_cData);
	printf("ABG_union2.ABG_fData = %p\n", &ABG_union2.ABG_fData);
	printf("ABG_union2.ABG_dData = %p\n\n\n", &ABG_union2.ABG_dData);

	printf("ABG_MyUnion ABG_union2 = %p\n\n", &ABG_union2);


	return(0);
}
