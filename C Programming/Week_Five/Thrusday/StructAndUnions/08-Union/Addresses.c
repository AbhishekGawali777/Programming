#include <stdio.h>

struct ABG_MyStruct
{
	int ABG_iData;
	char ABG_cData;
	float ABG_fData;
	double ABG_dData;
};

union ABG_MyUnion
{
	int ABG_iData;
	char ABG_cData;
	float ABG_fData;
	double ABG_dData;
};

int main(void)
{
	union ABG_MyUnion ABG_Union;
	struct ABG_MyStruct ABG_Structure;

	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyStruct' Are : \n\n");

	ABG_Structure.ABG_iData = 62;
	ABG_Structure.ABG_cData = 'K';
	ABG_Structure.ABG_fData = 25.93f;
	ABG_Structure.ABG_dData = 297.95697;

	printf("ABG_iData = %d\n", ABG_Structure.ABG_iData);
	printf("ABG_cData = %c\n", ABG_Structure.ABG_cData);
	printf("ABG_fData = %f\n", ABG_Structure.ABG_fData);
	printf("ABG_dData = %lf\n", ABG_Structure.ABG_dData);

	printf("\n\n");
	printf("Address Of Data Members Of 'struct ABG_MyStruct' Are : \n\n");
	printf("'ABG_iData' Occupies Address From %p\n", &ABG_Structure.ABG_iData);
	printf("'ABG_cData' Occupies Address From %p\n", &ABG_Structure.ABG_cData);
	printf("'ABG_fData' Occupies Address From %p\n", &ABG_Structure.ABG_fData);
	printf("'ABG_dData' Occupies Address  %p\n\n", &ABG_Structure.ABG_dData);


	printf("Members Of Union 'ABG_Union' Are : \n\n");

	ABG_Union.ABG_iData = 64;
	printf("ABG_Union.ABG_iData = %d\n", ABG_Union.ABG_iData);

	ABG_Union.ABG_cData = 'R';
	printf("ABG_Union.ABG_cData = %c\n", ABG_Union.ABG_cData);

	ABG_Union.ABG_fData = 92.316f;
	printf("ABG_Union.ABG_fData = %f\n", ABG_Union.ABG_fData);

	ABG_Union.ABG_dData = 163.21784;
	printf("ABG_Union.ABG_dData = %lf\n\n", ABG_Union.ABG_dData);

	printf("Address Of Members Of ABG_Union Are :\n\n");

	printf("ABG_Union.ABG_iData = %p\n", &ABG_Union.ABG_iData);
	printf("ABG_Union.ABG_cData = %p\n", &ABG_Union.ABG_cData);
	printf("ABG_Union.ABG_fData = %p\n", &ABG_Union.ABG_fData);
	printf("ABG_Union.ABG_dData = %p\n\n\n", &ABG_Union.ABG_dData);

	printf("ABG_MyUnion ABG_Union = %p\n\n", &ABG_Union);

	return(0);
}
