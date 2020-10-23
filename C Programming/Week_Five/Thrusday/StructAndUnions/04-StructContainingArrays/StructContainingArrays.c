#include <stdio.h>

#define ABG_INT_ARRAY_SIZE				10
#define ABG_CHAR_ARRAY_SIZE				26
#define ABG_FLOAT_ARRAY_SIZE			5

#define ABG_NUM_STRINGS					10
#define ABG_MAX_CHARACTERS_PER_STRING	20

#define ABG_ALPHABATE_BEGINING			65

struct ABG_MyDataOne
{
	int ABG_iArray[ABG_INT_ARRAY_SIZE];
	float ABG_fArray[ABG_FLOAT_ARRAY_SIZE];
};


struct ABG_MyDataTwo
{
	char ABG_cArray[ABG_CHAR_ARRAY_SIZE];
	char ABG_strArray[ABG_NUM_STRINGS][ABG_MAX_CHARACTERS_PER_STRING];
};

int main(void)
{
	int		ABG_iLoopCounter;
	struct	ABG_MyDataOne ABG_Data1;
	struct	ABG_MyDataTwo ABG_Data2;

	ABG_Data1.ABG_fArray[0] = 1.2f;
	ABG_Data1.ABG_fArray[1] = 2.3f;
	ABG_Data1.ABG_fArray[2] = 3.4f;
	ABG_Data1.ABG_fArray[3] = 4.5f;
	ABG_Data1.ABG_fArray[4] = 5.6f;

	printf("\n\n");
	printf("Enter %d Integers : \n\n", ABG_INT_ARRAY_SIZE);

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_INT_ARRAY_SIZE; ABG_iLoopCounter++)
		scanf("%d", &ABG_Data1.ABG_iArray[ABG_iLoopCounter]);

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_CHAR_ARRAY_SIZE; ABG_iLoopCounter++)
		ABG_Data2.ABG_cArray[ABG_iLoopCounter] = (char)(ABG_iLoopCounter + ABG_ALPHABATE_BEGINING);

	strcpy(ABG_Data2.ABG_strArray[0], "Welcome");
	strcpy(ABG_Data2.ABG_strArray[1], "This");
	strcpy(ABG_Data2.ABG_strArray[2], "Is");
	strcpy(ABG_Data2.ABG_strArray[3], "Astromedicomp's");
	strcpy(ABG_Data2.ABG_strArray[4], "Real");
	strcpy(ABG_Data2.ABG_strArray[5], "Time");
	strcpy(ABG_Data2.ABG_strArray[6], "Rendering");
	strcpy(ABG_Data2.ABG_strArray[7], "Batch");
	strcpy(ABG_Data2.ABG_strArray[8], "Of");
	strcpy(ABG_Data2.ABG_strArray[9], "2020-2021");

	printf("\n\n");
	printf("Members Of 'Struct ABG_MyDataOne' Along With Their Assigned Values Are :\n\n");
	printf("\n\n");
	
	printf("Interger Array (ABG_Data1.ABG_iArray[]) : \n\n");
	for(ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_INT_ARRAY_SIZE; ABG_iLoopCounter++)
		printf("ABG_Data1.ABG_iArray[%d] : %d\n", iLoopCounter, ABG_Data1.ABG_iArray[ABG_iLoopCounter]);

	printf("\n\n");
	printf("Floatint-Point Array (ABG_Data1.ABG_fArray[]) : \n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_FLOAT_ARRAY_SIZE; ABG_iLoopCounter++)
		printf("ABG_Data1.ABG_fArray[%d] : %f\n", ABG_iLoopCounter, ABG_Data1.ABG_fArray[ABG_iLoopCounter]);


	printf("\n\n");

	printf("Character Array (ABG_Data2.ABG_cArray[]) : \n\n");
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_CHAR_ARRAY_SIZE; ABG_iLoopCounter++)
		printf("ABG_Data1.ABG_iArray[%d] : %c\n", ABG_iLoopCounter, ABG_Data2.ABG_cArray[ABG_iLoopCounter]);

	printf("\n\n");
	printf("Floatint-Point Array (ABG_Data2.ABG_strArray[]) : \n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NUM_STRINGS; ABG_iLoopCounter++)
		printf("ABG_Data1.ABG_fArray[%d] : %s\n", ABG_iLoopCounter, ABG_Data2.ABG_strArray[ABG_iLoopCounter]);

	printf("\n\n");

	return(0);
}