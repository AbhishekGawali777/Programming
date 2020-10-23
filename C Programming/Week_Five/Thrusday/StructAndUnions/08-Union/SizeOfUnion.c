#include <stdio.h>

struct ABG_MyStructure
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
	union ABG_MyUnion ABG_UnionVar;
	struct ABG_MyStructure ABG_StrcutVar;

	printf("\n\n");
	printf("Size Of 'ABG_MyStructure' = %lu\n\n", sizeof(ABG_StrcutVar));
	printf("Size Of 'ABG_MyUnion' = %lu\n\n", sizeof(ABG_UnionVar));

	return(0);
}