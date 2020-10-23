#include <stdio.h>
#include <stdlib.h>

struct ABG_MyData
{
	int ABG_iNum;
	char ABG_cCh;
	float ABG_fNum;
	double ABG_dNum;
};

int main(void)
{
	// Variable Declarations

	int ABG_iIntSize;
	int ABG_iCharSize;
	int ABG_iFloatSize;
	int ABG_iDoubleSize;
	int ABG_iMyDataSize;
	int ABG_pMyDataSize;

	struct ABG_MyData* ABG_pstMyData = NULL;

	// Code

	printf("\n\n");

	ABG_pstMyData = (struct ABG_MyData*)malloc(sizeof(struct ABG_MyData));

	if (NULL == ABG_pstMyData)
	{
		printf("Cannot Allocate Memory For The 'struct ABG_MyData' \n\n");
		exit(0);
	}
	else
	{
		printf("Successfully Allocated Memory For The 'struct ABG_MyData' \n\n");
	}


	ABG_pstMyData->ABG_iNum = 55;
	ABG_pstMyData->ABG_cCh = 'A';
	ABG_pstMyData->ABG_fNum = 66.9f;
	ABG_pstMyData->ABG_dNum = 7425.14796;

	printf("\n\nData Members Of 'struct ABG_Mydata' Are :\n");
	printf("ABG_iNum = %d\n", ABG_pstMyData->ABG_iNum);
	printf("ABG_cCh  = %c\n", ABG_pstMyData->ABG_cCh);
	printf("ABG_fNum = %f\n", ABG_pstMyData->ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_pstMyData->ABG_dNum);

	ABG_iIntSize = sizeof(ABG_pstMyData->ABG_iNum);
	ABG_iCharSize = sizeof(ABG_pstMyData->ABG_cCh);
	ABG_iFloatSize = sizeof(ABG_pstMyData->ABG_fNum);
	ABG_iDoubleSize = sizeof(ABG_pstMyData->ABG_dNum);

	printf("\n\nSizes (In Bytes) Of Data Members Of 'struct ABG_Mydata' Are :\n");
	printf("Size Of ABG_iNum = %d\n", ABG_iIntSize);
	printf("Size Of ABG_cCh  = %d\n", ABG_iCharSize);
	printf("Size Of ABG_fNum = %d\n", ABG_iFloatSize);
	printf("Size Of ABG_dNum = %d\n", ABG_iDoubleSize);

	ABG_iMyDataSize = sizeof(struct ABG_MyData);
	ABG_pMyDataSize = sizeof(struct ABG_MyData*);

	printf("\n\n");
	printf("Size Of 'struct ABG_MyData' = %d bytes\n", ABG_iMyDataSize);
	printf("Size Of Pointer To 'struct ABG_Mydata' = %d bytes\n", ABG_pMyDataSize);

	if (ABG_pstMyData)
	{
		free(ABG_pstMyData);
		ABG_pstMyData = NULL;

		printf("Memory Allocated For 'ABG_pstMyData' Is Successfully Freed...!!!\n\n");
	}

	return(0);
}