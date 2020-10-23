// Header Files

#include <stdio.h>
#include <stdlib.h>

// Global Variable Declarations

int iQueueStatus = 0;

typedef struct frame
{
	int iData;
	struct frame* pNext;

}FRAME;

int main(void)
{
	// Functioon Declarations

	void Display(FRAME*);
	void Dequeue(FRAME**, FRAME**);
	void Enqueue(FRAME**, FRAME**, int);
	int  IsQueueEmpty(FRAME*);
	
	// Local Variable Declarations

	int iNumber;
	int iChoice;
	FRAME* pFirst	= NULL;
	FRAME* pLast	= NULL;

	// Code

	do
	{
		printf("1.) Enqueue\n2). Dequeue\n3.) Exit\n\n");

		printf("\n\nEnter Your Choice : \t");
		scanf_s("%d", &iChoice);
		printf("\n\n");

		switch (iChoice)
		{
		case 1:

			printf("\n\nEnter Integer Data To Enqueue :\t");
			scanf_s("%d", &iNumber);

			Enqueue(&pFirst, &pLast, iNumber);

			break;

		case 2:
			if (IsQueueEmpty(pFirst))
			{
				printf("\n\n************ Queue Is Empty ************\n\n");
				break;
			}

			Dequeue(&pFirst, &pLast);
			break;

		case 3:

			Display(pFirst);
			return(0);

		default:
			printf("\n\n*********************** Enter Valid Choice ***********************\n\n");
		}

		Display(pFirst);

	} while (1);

	return(0);
}

void Enqueue(FRAME** ppHead, FRAME** ppTail, int iNumber)
{
	// Local variable Declarations

	FRAME* pNewFrame = NULL;

	// Code

	pNewFrame = (FRAME*)malloc(sizeof(FRAME));

	if (NULL == pNewFrame)
	{
		printf("\n\nCannot Allocate Memory\n\n");
		return;
	}

	pNewFrame->iData  = iNumber;
	pNewFrame->pNext  = NULL;

	if (NULL == *ppHead && NULL == *ppTail)
	{
		*ppHead = pNewFrame;
		*ppTail = pNewFrame;
	}
	else
	{
		(*ppTail)->pNext = pNewFrame;
		*ppTail			 = pNewFrame;
	}
}

void Dequeue(FRAME** ppHead, FRAME** ppTail)
{
	// Local Variable Declarations

	FRAME* pTempNode = *ppHead;

	// Code
	
	if (NULL == *ppHead && NULL == *ppTail)
		return;

	if (*ppHead == *ppTail)
	{
		*ppHead = NULL;
		*ppTail = NULL;
	}
	else
	{
		*ppHead = (*ppHead)->pNext;
		
		pTempNode->pNext = NULL;
		pTempNode->iData = 0;
		
		free(pTempNode);
	}
}

void Display(FRAME* pHead)
{
	// Code

	if (IsQueueEmpty(pHead))
		return;

	printf("\n\nCurrent Queue Is :\t");

	while (pHead)
	{
		printf(" |%d| ", pHead->iData);
		pHead = pHead->pNext;
	}

	printf("\n\n");
}

int IsQueueEmpty(FRAME* pHead)
{
	// Code

	if (NULL == pHead)
		return (1);
	else
		return(0);
}
