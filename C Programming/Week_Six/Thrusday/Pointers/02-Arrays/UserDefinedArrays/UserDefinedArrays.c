#include <stdio.h>
#include <stdlib.h>

#define ABG_INT_SIZE		sizeof(int)
#define ABG_CHAR_SIZE		sizeof(char)
#define ABG_FLOAT_SIZE		sizeof(float)
#define ABG_DOUBLE_SIZE		sizeof(double)

int main(void)
{
	// Variable Declaration

	int* ABG_piArray = NULL;
	unsigned int ABG_uiIntegerArrayLength = 0;

	float* ABG_pfArray = NULL;
	unsigned int ABG_uiFloatArrayLength = 0;

	double* ABG_pdArray = NULL;
	unsigned int ABG_uiDoubleArrayLength = 0;

	char* ABG_pcArray = NULL;
	unsigned int ABG_uiCharacterArrayLength = 0;

	unsigned int ABG_uiLoopCounter;

	////////////////////			Integer Array				////////////////////////////


	printf("\n\n");
	printf("Enter The Number Of Elements You Want To In Integer Array : \t");
	scanf_s("%d", &ABG_uiIntegerArrayLength);

	ABG_piArray = (int*)malloc(ABG_uiIntegerArrayLength * ABG_INT_SIZE);

	if (NULL == ABG_piArray)
	{
		printf("\n\nCannot Allocate Memory For 'ABG_piArray' \n\n");
		exit(-1);
	}
	else
	{
		printf("\n\nMemory Allocation For Integer Array Has Successed...!!!\n\n");
	}

	printf("\n\nEnter %d Elements For The Integer Array :\n\n", ABG_uiIntegerArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiIntegerArrayLength; ABG_uiLoopCounter++)
	{
		printf("Enter Element Number %d:\t", ABG_uiLoopCounter + 1);
		scanf_s("%d", (ABG_piArray + ABG_uiLoopCounter));
	}

	////////////////////			Float Array				////////////////////////////


	printf("\n\n");
	printf("Enter The Number Of Elements You Want To In Float Array : \t");
	scanf_s("%d", &ABG_uiFloatArrayLength);

	ABG_pfArray = (float*)malloc(ABG_uiFloatArrayLength * ABG_FLOAT_SIZE);

	if (NULL == ABG_pfArray)
	{
		printf("\n\nCannot Allocate Memory For 'ABG_pfArray' \n\n");
		exit(-1);
	}
	else
	{
		printf("\n\nMemory Allocation For Float Array Has Successed...!!!\n\n");
	}

	printf("\n\nEnter %d Elements For The Float Array :\n\n", ABG_uiFloatArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiFloatArrayLength; ABG_uiLoopCounter++)
	{
		printf("Enter Element Number %d:\t", ABG_uiLoopCounter + 1);
		scanf_s("%f", (ABG_pfArray + ABG_uiLoopCounter));
	}

	
	
	
	////////////////////			Double Array				////////////////////////////



	printf("\n\n");
	printf("Enter The Number Of Elements You Want To In Double Array : \t");
	scanf_s("%d", &ABG_uiDoubleArrayLength);

	ABG_pdArray = (double*)malloc(ABG_uiDoubleArrayLength * ABG_DOUBLE_SIZE);

	if (NULL == ABG_pdArray)
	{
		printf("\n\nCannot Allocate Memory For 'ABG_pdArray' \n\n");
		exit(-1);
	}
	else
	{
		printf("\n\nMemory Allocation For Double Array Has Successed...!!!\n\n");
	}

	printf("\n\nEnter %d Elements For The Double Array :\n\n", ABG_uiDoubleArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiDoubleArrayLength; ABG_uiLoopCounter++)
	{
		printf("Enter Element Number %d:\t", ABG_uiLoopCounter + 1);
		scanf_s("%lf", (ABG_pdArray + ABG_uiLoopCounter));
	}



	////////////////////			Character Array				////////////////////////////



	printf("\n\n");
	printf("Enter The Number Of Elements You Want To In Character Array : \t");
	scanf_s("%d", &ABG_uiCharacterArrayLength);

	ABG_pcArray = (char*)malloc(ABG_uiCharacterArrayLength * ABG_CHAR_SIZE);

	if (NULL == ABG_pcArray)
	{
		printf("\n\nCannot Allocate Memory For 'ABG_pcArray'\n\n");
		exit(-1);
	}
	else
	{
		printf("\n\nMemory Allocation For Character Array Has Successed...!!!\n\n");
	}

	printf("\n\nEnter %d Elements For The Character Array :\n\n", ABG_uiCharacterArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiCharacterArrayLength; ABG_uiLoopCounter++)
	{
		printf("Enter Element Character %d:\t", ABG_uiLoopCounter + 1);
		//scanf_s("%c", (ABG_pcArray + ABG_uiLoopCounter), 1);
		*(ABG_pcArray + ABG_uiLoopCounter) = getch();
		printf("%c\n", *(ABG_pcArray + ABG_uiLoopCounter));
	}

	//////////////////////			Displaying Arrays			//////////////////////////


	////////////////////			Integer Array				////////////////////////////

	printf("\n\n");
	printf("\n\n The Integer Array Entered By You, Consisting Of %d Elements :\n\n", ABG_uiIntegerArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiIntegerArrayLength; ABG_uiLoopCounter++)
		printf("%d \t\t At Adress %p\n", *(ABG_piArray + ABG_uiLoopCounter), (ABG_piArray + ABG_uiLoopCounter));


	////////////////////			Float Array				////////////////////////////

	printf("\n\n");
	printf("\n\n The Float Array Entered By You, Consisting Of %d Elements :\n\n", ABG_uiFloatArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiFloatArrayLength; ABG_uiLoopCounter++)
		printf("%f \t\t At Adress %p\n", *(ABG_pfArray + ABG_uiLoopCounter), (ABG_pfArray + ABG_uiLoopCounter));

	
	////////////////////			Double Array				////////////////////////////

	printf("\n\n");
	printf("\n\n The Double Array Entered By You, Consisting Of %d Elements :\n\n", ABG_uiDoubleArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiDoubleArrayLength; ABG_uiLoopCounter++)
		printf("%lf \t\t At Adress %p\n", *(ABG_pdArray + ABG_uiLoopCounter), (ABG_pdArray + ABG_uiLoopCounter));


	////////////////////			Character Array				////////////////////////////


	printf("\n\n");
	printf("\n\n The Character Array Entered By You, Consisting Of %d Elements :\n\n", ABG_uiCharacterArrayLength);

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_uiCharacterArrayLength; ABG_uiLoopCounter++)
		printf("%c \t\t At Adress %p\n", *(ABG_pcArray + ABG_uiLoopCounter), (ABG_pcArray + ABG_uiLoopCounter));


	//////////////////////			Freeing Memory			//////////////////////////

	if (ABG_piArray)
	{
		free(ABG_piArray);
		ABG_piArray = NULL;

		printf("\n\nMemory Allocated For Integer Array Is Freed Successfully..!!!");
	}


	if (ABG_pfArray)
	{
		free(ABG_pfArray);
		ABG_pfArray = NULL;

		printf("\n\nMemory Allocated For Float Array Is Freed Successfully..!!!");
	}


	if (ABG_pdArray)
	{
		free(ABG_pdArray);
		ABG_pdArray = NULL;

		printf("\n\nMemory Allocated For Double Array Is Freed Successfully..!!!");
	}


	if (ABG_pcArray)
	{
		free(ABG_pcArray);
		ABG_pcArray = NULL;

		printf("\n\nMemory Allocated For Character Array Is Freed Successfully..!!!");
	}

	return(0);
}