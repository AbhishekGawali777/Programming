#include <stdio.h>

struct ABG_MyData
{
	int ABG_iNum;
	float ABG_fNum;
	double ABG_dNum;
};


int main(void)
{
	// Function Declaration

	void ABG_ChangeValues(struct ABG_MyData*);

	// Variable Declaration
	
	struct ABG_MyData* ABG_pData = NULL;

	//Code

	printf("\n\n");

	ABG_pData = (struct ABG_MyData*)malloc(sizeof(struct ABG_MyData));

	if (NULL == ABG_pData)
	{
		printf("Cannot Allocate Memory For 'ABG_MyData'\n\n");
		exit(0);
	}
	else
	{
		printf("Successfully Allocated Memory For 'ABG_MyData'\n\n");
	}

	ABG_pData->ABG_iNum = 97;
	ABG_pData->ABG_fNum = 32.97f;
	ABG_pData->ABG_dNum = 145.1333665;

	printf("\n\nData Members Of 'struct ABG_MyData' Are :\n\n");
	printf("ABG_iNum = %d\n", ABG_pData->ABG_iNum);
	printf("ABG_fNum = %f\n", ABG_pData->ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_pData->ABG_dNum);

	printf("\n\n");

	ABG_ChangeValues(ABG_pData);

	printf("\n\nData Members Of 'struct ABG_MyData' Are :\n\n");
	printf("ABG_iNum = %d\n", ABG_pData->ABG_iNum);
	printf("ABG_fNum = %f\n", ABG_pData->ABG_fNum);
	printf("ABG_dNum = %lf\n", ABG_pData->ABG_dNum);

	printf("\n\n");

	if (ABG_pData)
	{
		free(ABG_pData);
		ABG_pData = NULL;

		printf("Memory Allocated For 'ABG_pData' Is Successfully  Freed..!!!\n\n");
	}

	return(0);
}

void ABG_ChangeValues(struct ABG_MyData* ABG_pMyData)
{
	ABG_pMyData->ABG_iNum = 132;
	ABG_pMyData->ABG_fNum = 17.98f;
	ABG_pMyData->ABG_dNum = 7415.999999;
}