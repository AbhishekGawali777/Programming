
// Header Files

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

// Global Variable Declarations

int iFrameCount = 0;

typedef struct frame
{
	int 			iData;
	struct frame*	pNext;
}FRAME;

// main()

int main(void)
{
	// Functions Declarations

	void Display(FRAME*);
	int  PopFrame(FRAME**);
	void PushFrame(int, FRAME**);

	// Local Variable Declarations

	int iData;
	int iChoice;
	FRAME* pfStack = NULL;
	
	// Code

	do
	{
		printf("\n\n\n1. Push Data \n2. Pop Data \n3.Exit\n\n");

		printf("Enter Choice : ");
		scanf_s("%d", &iChoice);
		printf("\n\n");

		switch (iChoice)
		{
		case 1:
			printf("\nEnter Data : ");
			scanf_s("%d", &iData);

			PushFrame(iData, &pfStack);
			break;

		case 2:
			iData = PopFrame(&pfStack);

			if (iData != -1)
				printf("\n\nPopped Frame Contains Data : %d\n\n", iData);
			else
				printf("\n\nThere Is Nothing To Pop...!!!\n\n");

			break;

		case 3:
			if (pfStack)
			{
				free(pfStack);
				pfStack = NULL;
			}
			exit(0);

		default:
			printf("\n\n+-+-+-+-+-+-+-+-+-+-+- Enter Valid Choice -+-+-+-+-+-+-+-+-+-+-+-\n\n");
			break;
		}

		if (STACK_SIZE == iFrameCount)
		{
			printf("\n\nStack Is Full...!!!\n\n");
		}
		else if (0 == iFrameCount)
		{
			printf("\nStack Is Empty...!!!\n\n");
		}

		Display(pfStack);

	} while (1);

	return(0);
}

void PushFrame(int iData, FRAME** pfStack)
{
	// Local Function Declarations

	int IsStackEmpty(FRAME*);
	
	// Local Variable Declarations

	FRAME* pNewFrame = NULL;

	// Code

	if (IsStackFull(*pfStack))
		return;

	pNewFrame = (FRAME*)malloc(sizeof(FRAME));

	if (NULL == pNewFrame)
	{
		printf("\n\nMalloc Failed\n\n");
		return;
	}

	pNewFrame->iData = iData;
	pNewFrame->pNext = NULL;

	if (NULL != (*pfStack))
	{
		pNewFrame->pNext = *pfStack;
	}

	*pfStack = pNewFrame;
	iFrameCount++;
}

int PopFrame(FRAME** pfStack)
{
	// Local Function Declarations
	
	int IsStackEmpty(FRAME*);

	// Local Variable Declarations

	int iPoppedData;
	FRAME* pDeleteFrame = NULL;

	// Code

	if (IsStackEmpty(*pfStack))
		return(-1);

	pDeleteFrame = *pfStack;

	*pfStack = pDeleteFrame->pNext;

	iPoppedData = pDeleteFrame->iData;

	free(pDeleteFrame);
	pDeleteFrame = NULL;

	iFrameCount--;

	return(iPoppedData);
}

void Display(FRAME* pfStack)
{
	// Code

	if (NULL == pfStack)
		return;

	printf("\n\nFrame Present In Stack are :\t");

	while (pfStack)
	{
		printf(" |%d| ", pfStack->iData);
		pfStack = pfStack->pNext;
	}

	printf("\n\n");
}

int IsStackEmpty(FRAME* pfStack)
{
	//Todo

	if (NULL == pfStack || 0 == iFrameCount)
		return(1);
	else
		return(0);
}

int IsStackFull(FRAME* pfStack)
{
	if (STACK_SIZE == iFrameCount)
		return(1);
	else
		return(0);
			
}

