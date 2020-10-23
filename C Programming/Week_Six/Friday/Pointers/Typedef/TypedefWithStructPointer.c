#include <stdio.h>
#include <stdlib.h>

struct ABG_MyData
{
	int ABG_iNum;
	float ABG_fNum;
	double ABG_dNum;
};

int main(void)
{
	// Variable Declarations

	int ABG_iIntSize;
	int ABG_iFloatSize;
	int ABG_iDoubleSize;
	int ABG_iStructMyDataSize;
	int ABG_pStructMyDataSize;

	typedef struct ABG_MyData* ABG_MyDataPtr;

	ABG_MyDataPtr ABG_pData;

	// Code

	printf("\n\n");

	ABG_pData = (ABG_MyDataPtr)malloc(sizeof(struct ABG_MyData));

	if (NULL == ABG_pData)
	{
		printf("\n\nFailed To Allocated Memory To 'struct ABG_MyData'\n\n");
		exit(0);
	}
	else
	{
		printf("Successfully Allocated Memory For 'struct ABG_MyData'\n\n");
	}

	ABG_pData->ABG_iNum = 97;
	ABG_pData->ABG_fNum = 56.74f;
	ABG_pData->ABG_dNum = 7821.77784;

	printf("\n\n");
	printf("Data Members Of 'struct ABG_MyData' Are:\n\n");

	printf("ABG_iNum = %d\n", ABG_pData->ABG_iNum);
	printf("ABG_fNum = %f\n", ABG_pData->ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_pData->ABG_dNum);

	ABG_iIntSize = sizeof(ABG_pData->ABG_iNum);
	ABG_iFloatSize = sizeof(ABG_pData->ABG_fNum);
	ABG_iDoubleSize = sizeof(ABG_pData->ABG_dNum);

	printf("\n\n");
	printf("Sizes (In Bytes) Of Data Members Of 'strucct ABG_MyData' Are:\n\n");
	printf("Size Of ABG_iNum = %d Bytes\n", ABG_iIntSize);
	printf("Size Of ABG_fNum = %d Bytes\n", ABG_iFloatSize);
	printf("Size Of ABG_dNum = %d Bytes\n", ABG_iDoubleSize);


	ABG_iStructMyDataSize = sizeof(struct ABG_MyData);
	ABG_pStructMyDataSize = sizeof(ABG_MyDataPtr);

	printf("\n\n");
	printf("Size Of 'struct ABG_MyData' : %d Bytes\n ", ABG_iStructMyDataSize);
	printf("Size Of Pointer To'struct ABG_MyData' : %d Bytes\n\n", ABG_pStructMyDataSize);

	if (ABG_pData)
	{
		free(ABG_pData);
		ABG_pData = NULL;

		printf("Memory Allocated For 'struct ABG_pData' Has Been Successfully Freed..!!\n\n");
	}
	return(0);
}