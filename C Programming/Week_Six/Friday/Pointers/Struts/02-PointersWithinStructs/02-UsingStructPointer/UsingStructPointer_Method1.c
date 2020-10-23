#include <stdio.h>
#include <stdlib.h>

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

	struct ABG_MyData* ABG_pData = NULL;

	// Code

	printf("\n\n");
	ABG_pData = (struct ABG_MyData*)malloc(sizeof(struct ABG_MyData));

	if (NULL == ABG_pData)
	{
		printf("Cannot Allocate Memory For The 'struct ABG_pData' \n\n");
		exit(0);
	}
	else
	{
		printf("Successfully Allocated Memory For The 'struct ABG_MyData' \n\n");
	}



	(*ABG_pData).ABG_iNum = 12;	
	(*ABG_pData).ABG_iPtr = &(*ABG_pData).ABG_iNum;

	(*ABG_pData).ABG_fNum = 96.47f;
	(*ABG_pData).ABG_fPtr = &(*ABG_pData).ABG_fNum;

	(*ABG_pData).ABG_dNum = 8972.17852;
	(*ABG_pData).ABG_dPtr = &(*ABG_pData).ABG_dNum;


	printf("\n\n");
	printf("ABG_iNum = %d\n", *((*ABG_pData).ABG_iPtr));
	printf("Address Of ABG_iNum = %p\n", (*ABG_pData).ABG_iPtr);

	printf("\n\n");
	printf("ABG_fNum = %f\n", *((*ABG_pData).ABG_fPtr));
	printf("Address Of ABG_fNum = %p\n", (*ABG_pData).ABG_fPtr);

	printf("\n\n");
	printf("ABG_dNum = %lf\n", *((*ABG_pData).ABG_dPtr));
	printf("Address Of ABG_dNum = %p\n", (*ABG_pData).ABG_dPtr);


	if (ABG_pData)
	{
		free(ABG_pData);
		ABG_pData = NULL;

		printf("\n\nMemory Allocated For 'ABG_pData' Is Successfully Freed...!!!\n\n");
	}

	return(0);
}