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
	// Function Declaration
	struct ABG_MyData ABG_AddStructMembers(struct ABG_MyData, struct ABG_MyData, struct ABG_MyData);

	// Variable Declaration
	struct ABG_MyData ABG_stData1, ABG_stData2, ABG_stData3, ABG_stAnswer;

	// Code 
	
	printf("\n\n\n\n");
	printf("********* DATA 1 ***********\n\n");

	printf("Enter Integer value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData1' : ");
	scanf_s("%d", &ABG_stData1.ABG_iData);

	printf("\n\n");
	printf("Enter Character value For 'ABG_cData' Of 'struct ABG_MyData ABG_stData1' : ");
	ABG_stData1.ABG_cData = getche();

	printf("\n\n");
	printf("Enter Floating-Point value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData1' : ");
	scanf_s("%f", &ABG_stData1.ABG_fData);

	printf("\n\n");
	printf("Enter Double value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData1' : ");
	scanf_s("%lf", &ABG_stData1.ABG_dData);

	printf("\n\n\n\n");
	printf("********* DATA 2 ***********\n\n");

	printf("Enter Integer value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData2' : ");
	scanf_s("%d", &ABG_stData2.ABG_iData);

	printf("\n\n");
	printf("Enter Character value For 'ABG_cData' Of 'struct ABG_MyData ABG_stData2' : ");
	ABG_stData2.ABG_cData = getche();

	printf("\n\n");
	printf("Enter Floating-Point value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData2' : ");
	scanf_s("%f", &ABG_stData2.ABG_fData);

	printf("\n\n");
	printf("Enter Double value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData2' : ");
	scanf_s("%lf", &ABG_stData2.ABG_dData);

	printf("\n\n\n\n");
	printf("********* DATA 3 ***********\n\n");

	printf("Enter Integer value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData3' : ");
	scanf_s("%d", &ABG_stData3.ABG_iData);


	printf("\n\n");
	printf("Enter Character value For 'ABG_cData' Of 'struct ABG_MyData ABG_stData3' : ");
	ABG_stData3.ABG_cData = getche();

	printf("\n\n");
	printf("Enter Floating-Point value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData3' : ");
	scanf_s("%f", &ABG_stData3.ABG_fData);

	printf("\n\n");
	printf("Enter Double value For 'ABG_iData' Of 'struct ABG_MyData ABG_stData3' : ");
	scanf_s("%lf", &ABG_stData3.ABG_dData);


	ABG_stAnswer = ABG_AddStructMembers(ABG_stData1, ABG_stData2, ABG_stData3);

	printf("\n\n\n\n");
	printf("******* ANSWER *********\n\n");
	printf("ABG_stAnswer.ABG_iData = %d\n", ABG_stAnswer.ABG_iData);
	printf("ABG_stAnswer.ABG_cData = %c\n", ABG_stAnswer.ABG_cData);
	printf("ABG_stAnswer.ABG_fData = %f\n", ABG_stAnswer.ABG_fData);
	printf("ABG_stAnswer.ABG_dData = %lf\n\n", ABG_stAnswer.ABG_dData);

	ABG_stAnswer.ABG_cData = ABG_stData1.ABG_cData;
	printf("ABG_stAnswer.ABG_cData (From ABG_stData1) = %c\n", ABG_stAnswer.ABG_cData);

	ABG_stAnswer.ABG_cData = ABG_stData2.ABG_cData;
	printf("ABG_stAnswer.ABG_cData (From ABG_stData2) = %c\n", ABG_stAnswer.ABG_cData);

	ABG_stAnswer.ABG_cData = ABG_stData3.ABG_cData;
	printf("ABG_stAnswer.ABG_cData (From ABG_stData3) = %c\n", ABG_stAnswer.ABG_cData);

	return(0);
}

struct ABG_MyData ABG_AddStructMembers(struct ABG_MyData ABG_stFirstData, struct ABG_MyData ABG_stSecondData,
										struct ABG_MyData ABG_stThirdData)
{
	// Variable Declaration
	struct ABG_MyData ABG_stAnswer;

	//Code

	ABG_stAnswer.ABG_iData = ABG_stFirstData.ABG_iData + ABG_stSecondData.ABG_iData + ABG_stThirdData.ABG_iData;
	ABG_stAnswer.ABG_fData = ABG_stFirstData.ABG_fData + ABG_stSecondData.ABG_fData + ABG_stThirdData.ABG_fData;
	ABG_stAnswer.ABG_dData = ABG_stFirstData.ABG_dData + ABG_stSecondData.ABG_dData + ABG_stThirdData.ABG_dData;

	return(ABG_stAnswer);
}
