
// Header Files

#include <stdio.h>
#include <stdlib.h>

// Structure Declaration

// psn	- Pointer To Struct Node
// pn	- Pointer To NODE

typedef struct node
{
	struct node* psnPrev;
	int iData;
	struct node* psnNext;
}NODE;


// main()

int main(void)
{
	// Function Declarations

	// Insertion

	void InsertLast(NODE**, NODE**, int);
	void InsertFirst(NODE**, NODE**, int);
	void InsertAtPosition(NODE**, NODE**, int, int);

	// Deletion

	void DeleteLast(NODE**, NODE**);
	void DeleteFirst(NODE**, NODE**);
	void DeleteAtPosition(NODE**, NODE**, int);

	// Search

	int SearchLastOccurance(NODE*, NODE*, int);
	int SearchAllOccurances(NODE*, NODE*, int);
	int SearchFirstOccurance(NODE*, NODE*, int);

	void Display(NODE*, NODE*);
	void FreeAllAllocatedMemory(NODE**, NODE**);
	
	// Local Variable Declarations

	int iNum;
	int iPosition;
	unsigned int iChoice;

	NODE* psnFirst	= NULL;
	NODE* psnLast	= NULL;

	// Code

	do
	{
		printf("\n\n");

		printf("\t\t\t\t1.) Insert.\n\
				2.) Delete\n \
				3.) Search\n \
				4). Node Count\n \
				5.) Exit.\n\n");


		printf("Enter Your Choice:\t");
		fflush(stdin);
		scanf_s("%d", &iChoice);

		switch (iChoice)
		{
		case 1:

			printf("\n\n");

			do
			{
				printf("\t\t\t\t\t1.) Insert At First Position\n \
					2.) Insert At Last Position\n \
					3.) Insert In Between The List\n \
					4.) Back To Main Menu\n\n");

				printf("\nEnter Choice For Method Of Insertion:\t");
				fflush(stdin);
				scanf_s("%d", &iChoice);

				printf("\n\n");

				switch (iChoice)
				{
				case 1:
					printf("Enter Number :\t");
					scanf_s("%d", &iNum);

					InsertFirst(&psnFirst, &psnLast, iNum);

					break;

				case 2:
					printf("Enter Number :\t");
					scanf_s("%d", &iNum);

					InsertLast(&psnFirst, &psnLast, iNum);

					break;

				case 3:

					printf("Enter Position :\t");
					scanf_s("%d", &iPosition);

					if (iPosition > (CountNode(psnFirst, psnLast)) + 1 || iPosition < 1)
					{
						printf("\n\n+-+-+-+-+-+-+-+-+-+- Enter valid Position +-+-+-+-+-+-+-+-+-+-\n\n");
						break;
					}

					printf("\n");

					printf("Enter Number :\t");
					scanf_s("%d", &iNum);

					InsertAtPosition(&psnFirst, &psnLast, iPosition, iNum);

					break;

				case 4:
					break;

				default:

					printf("\n\n+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-\n\n");
					break;
				}

				Display(psnFirst, psnLast);

			} while (4 != iChoice);
		
			break;

		case 2:
			
			do
			{
				if (NULL == psnFirst && NULL == psnLast)
				{
					printf("\n\nFor Now There Is Nothing To Delete, As List Is Empty..!!!\n\n");
					break;
				}
				else
					Display(psnFirst, psnLast);

				printf("\n\n");

				printf("\t\t\t\t\t1.) Delete From First Position\n \
					2.) Delete From Last Position\n \
					3.) Delete In Between The List\n \
					4.) Back To Main Menu\n\n");

				printf("Enter Choice For Method Of Deletion:\t");
				fflush(stdin);
				scanf_s("%d", &iChoice);

			
				switch (iChoice)
				{

				case 1:
					DeleteFirst(&psnFirst, &psnLast);

					break;

				case 2:
					DeleteLast(&psnFirst, &psnLast);

					break;

				case 3:

					printf("\n\nEnter Position : \t");
					fflush(stdin);
					scanf_s("%d", &iPosition);

					if (iPosition > (CountNode(psnFirst, psnLast)) || iPosition < 1)
					{
						printf("\n\n+-+-+-+-+-+-+-+-+-+- Enter valid Position +-+-+-+-+-+-+-+-+-+-\n\n");
						break;
					}

					DeleteAtPosition(&psnFirst, &psnLast, iPosition);

					break;

				case 4:
					break;

				default:

					printf("\n\n+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-\n\n");
					break;
				}

			} while (4 != iChoice);
			
			break;
		
		case 3:
		
			if (NULL == psnFirst && NULL == psnLast)
			{
				printf("\n\nThere Is Nothing To Search, As List Is Empty..!!!\n\n");
				break;
			}

			do 
			{
				printf("\n\n");

				printf("\t\t\t\t\t1.) Search First Occurance Data\n \
					2.) Search Last Occurance Of Data\n \
					3.) Search All Occurances Of Data\n \
					4.) Back To Main Menu\n\n");

				printf("Enter Choice For Method Of Searching:\t");
				fflush(stdin);
				scanf_s("%d", &iChoice);

				if (4 == iChoice)
					break;

				printf("\n\nEnter Number To Find Occurance Of:\t");
				fflush(stdin);
				scanf_s("%d", &iNum);

				switch (iChoice)
				{
				case 1:

					iPosition = SearchFirstOccurance(psnFirst, psnLast, iNum);

					if (-1 == iPosition)
						printf("\n\nNo Occurance Found For Entered Data = %d\n\n", iNum);
					else
						printf("\n\nFirst Occurance Of Data \'%d\' Found At Position \'%d\' In The List.\n\n", iNum, iPosition);

					break;

				case 2:

					iPosition = SearchLastOccurance(psnFirst, psnLast, iNum);

					if (-1 == iPosition)
						printf("\n\nNo Occurance Found For Entered Data = %d\n\n", iNum);
					else
						printf("\n\nLast Occurance Of Data \'%d\' Found At Position \'%d\' In The List.\n\n", iNum, iPosition);

					break;

				case 3:
					iPosition = SearchAllOccurances(psnFirst, psnLast, iNum);

					if (-1 == iPosition)
						printf("\n\nNo Occurance Found For Entered Data = %d\n\n", iNum);
					else
						printf("\n\nThere are \'%d\' Occurances Found For Number \'%d\' In The List\n\n", iPosition, iNum);

					break;


				case 4:
					break;

				default:

					printf("\n\n+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-\n\n");
					break;
				}
				
				Display(psnFirst, psnLast);

			} while (4 != iChoice);

			break;

		case 4:

			if (NULL == psnFirst)
			{
				printf("\n\nNothing To Count, As Linked List Empty...!!!\n\n");
					break;
			}

			iNum = CountNode(psnFirst, psnLast);

			printf("\n\nNumber Of Nodes In The List Are : %d\n\n", iNum);
			break;

		case 5:
			Display(psnFirst, psnLast);
			FreeAllAllocatedMemory(&psnFirst, &psnLast);
			
			psnFirst	= NULL;
			psnLast		= NULL;
			return(0);

		default:
			printf("\n\n+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-\n\n");
		}

	} while (1);

	return(0);
}

void InsertFirst(NODE** ppnHead, NODE** ppnTail, int iNum)
{
	// Local Variable Declaration

	NODE* pnNewNode = NULL;

	// Code

	pnNewNode = (NODE*)malloc(sizeof(NODE));

	if (NULL == pnNewNode)
	{
		printf("\n\n Cannot Allocate Memory\n\n");
		return;
	}

	pnNewNode->psnPrev	= NULL;
	pnNewNode->iData	= iNum;
	pnNewNode->psnNext	= NULL;

	if (*ppnHead == NULL && NULL == *ppnTail)
	{
		*ppnHead			= pnNewNode;
		*ppnTail			= pnNewNode;
		pnNewNode->psnNext	= *ppnHead;
		pnNewNode->psnPrev	= *ppnTail;

		return;
	}

	pnNewNode->psnNext	= *ppnHead;
	pnNewNode->psnPrev	= *ppnTail;
	(*ppnHead)->psnPrev = pnNewNode;
	*ppnHead			= pnNewNode;
	(*ppnTail)->psnNext = pnNewNode;
}

void InsertLast(NODE** ppnHead, NODE** ppnTail, int iNum)
{
	// Function Declarations

	void InsertFirst(NODE**, NODE**, int);

	// Local Variable Declarations

	NODE* pnNewNode	= NULL;

	// Code

	pnNewNode = (NODE*)malloc(sizeof(NODE));

	if (NULL == pnNewNode)
	{
		printf("\n\nCannot Allocate Memory.\n\n");
		return;
	}

	if (NULL == *ppnHead && NULL == *ppnTail)
	{
		InsertFirst(ppnHead, ppnTail, iNum);
		return;
	}

	pnNewNode->psnPrev	= NULL;
	pnNewNode->iData	= iNum;
	pnNewNode->psnNext	= NULL;

	pnNewNode->psnNext	= (*ppnTail)->psnNext;
	(*ppnTail)->psnNext	= pnNewNode;
	pnNewNode->psnPrev	= *ppnTail;
	(*ppnHead)->psnPrev = pnNewNode;
	*ppnTail			= pnNewNode;
}

void InsertAtPosition(NODE** ppnHead, NODE** ppnTail, int iPosition, int iNum)
{
	// Function Decalrations

	int  CountNodes(NODE*, NODE*);
	void InsertLast(NODE**, NODE**, int);
	void InsertFirst(NODE**, NODE**, int);

	// Local Variable Declarations

	NODE* pnNewNode	 = NULL;
	NODE* pnTempNode = NULL;

	// Code
	
	if (1 == iPosition)
	{

		InsertFirst(ppnHead, ppnTail, iNum);
		return;
	}
	else if (iPosition == CountNode(*ppnHead, *ppnTail) + 1)
	{
		InsertLast(ppnHead, ppnTail, iNum);
		return;
	}
	
	pnNewNode = (NODE*)malloc(sizeof(NODE));

	if (NULL == pnNewNode)
	{
		printf("\n\nCannot Allocate Memory\n\n");
		return;
	}

	pnNewNode->psnPrev	= NULL;
	pnNewNode->iData	= iNum;
	pnNewNode->psnNext	= NULL;

	pnTempNode = *ppnHead;

	while (iPosition - 2)
	{
		pnTempNode = pnTempNode->psnNext;

		iPosition--;
	}

	pnNewNode->psnNext				= pnTempNode->psnNext;
	pnNewNode->psnNext->psnPrev		= pnNewNode;
	pnNewNode->psnPrev				= pnTempNode;
	pnTempNode->psnNext				= pnNewNode;
}


void DeleteFirst(NODE** ppnHead, NODE** ppnTail)
{
	// Code

	if (NULL == *ppnHead)
		return;
	
	if (*ppnHead != *ppnTail)
	{
		(*ppnTail)->psnNext = (*ppnHead)->psnNext;
		(*ppnHead)->psnNext->psnPrev = *ppnTail;
	}

	printf("\n\nDeleted Node : %d \n\n", (*ppnHead)->iData);

	(*ppnHead)->psnNext 	= NULL;
	(*ppnHead)->iData   	= 0;
	(*ppnHead)->psnPrev 	= NULL;

	free(*ppnHead);

	if(*ppnHead != *ppnTail)
		*ppnHead = (*ppnTail)->psnNext;
	
	else
	{
		*ppnHead = NULL;
		*ppnTail = NULL;
	}
}

void DeleteLast(NODE** ppnHead, NODE** ppnTail)
{
	// Code

	if (NULL == *ppnHead)
		return;

	if (*ppnTail != *ppnHead)
	{
		(*ppnTail)->psnPrev->psnNext = *ppnHead;
		(*ppnHead)->psnPrev = (*ppnTail)->psnPrev;
	}

	printf("\n\nDeleted Node : %d \n\n", (*ppnTail)->iData);

	(*ppnTail)->psnNext		= NULL;
	(*ppnTail)->iData		= 0;
	(*ppnTail)->psnPrev		= NULL;

	free(*ppnTail);

	if (*ppnTail != *ppnHead)
	{
		*ppnTail = (*ppnHead)->psnPrev;
	}
	else
	{
		*ppnHead = NULL;
		*ppnTail = NULL;
	}
}

void DeleteAtPosition(NODE** ppnHead, NODE** ppnTail, int iPosition)
{
	// Local Variable Declaration

	NODE* pnTempNode = NULL;

	// Code

	if (1 == iPosition)
	{
		DeleteFirst(ppnHead, ppnTail);
		return;
	}
	else if (iPosition == CountNode(*ppnHead, *ppnTail))
	{
		DeleteLast(ppnHead, ppnTail);
		return;
	}

	pnTempNode = *ppnHead;

	while (iPosition - 1)
	{
		pnTempNode = pnTempNode->psnNext;

		iPosition--;
	}

	pnTempNode->psnPrev->psnNext = pnTempNode->psnNext;
	pnTempNode->psnNext->psnPrev = pnTempNode->psnPrev;
	
	printf("\n\nDeleted Node : %d \n\n", pnTempNode->iData);

	free(pnTempNode);
}

int SearchFirstOccurance(NODE* pnHead, NODE* pnTail, int iNum)
{
	// Local Variable Declarations

	int iLoopCounter = 1;

	// Code

	while (pnHead->iData != iNum && pnHead != pnTail)
	{
		pnHead = pnHead->psnNext;
		iLoopCounter++;
	}

	if (pnHead->iData != iNum)
		return(-1);
	else
		return(iLoopCounter);

}

int SearchLastOccurance(NODE* pnHead, NODE* pnTail, int iNum)
{
	// Local Variable Declarations

	int iLoopCounter;

	// Code

	iLoopCounter = CountNode(pnHead, pnTail);

	while (pnTail->iData != iNum && pnTail != pnHead)
	{
		pnTail = pnTail->psnPrev;
		iLoopCounter--;
	}

	if (pnTail->iData != iNum)
		return(-1);
	else
		return(iLoopCounter);


}

int SearchAllOccurances(NODE* pnHead, NODE* pnTail, int iNum)
{
	// Local Variable Declarations

	int iLoopCounter = 0;

	// Code

	while (pnHead != pnTail)
	{
		if (pnHead->iData == iNum)
			iLoopCounter++;

		pnHead = pnHead->psnNext;
	}

	if (pnHead->iData == iNum)
		iLoopCounter++;

	if (0 == iLoopCounter)
		return(-1);
	else
		return(iLoopCounter);

}

int CountNode(NODE* pnHead, NODE* pnTail)
{
	// Local Variable Declaration

	int iLoopCounter = 1;

	// Code 

	while (pnHead != pnTail)
	{
		pnHead = pnHead->psnNext;
		iLoopCounter++;
	}

	return(iLoopCounter);
}

void Display(NODE* pnHead, NODE* pnTail)
{
	// Code

	if (NULL == pnHead)
	{
		printf("\n\n********************* Linked List Is Empty *********************\n\n");
		return;
	}

	printf("\n\nLinked List Is :\t");

	while (pnHead != pnTail)
	{
		printf("->|%d|", pnHead->iData);
		pnHead = pnHead->psnNext;
	}

	printf("->|%d|", pnHead->iData);

	printf("\n\n");
}

void FreeAllAllocatedMemory(NODE** ppnHead, NODE** ppnTail)
{
	// Code

	if (NULL == *ppnHead && NULL == *ppnTail)
		return;

	while (*ppnTail != *ppnHead)
	{
		(*ppnHead)->psnPrev = (*ppnTail)->psnPrev;
		(*ppnTail)->psnPrev = NULL;
		(*ppnTail)->iData	= 0;
		(*ppnTail)->psnNext = NULL;

		free(*ppnTail);

		*ppnTail = (*ppnHead)->psnPrev;
	}

	(*ppnHead)->psnNext = NULL;
	(*ppnHead)->iData	= 0;
	(*ppnHead)->psnPrev = NULL;
}
