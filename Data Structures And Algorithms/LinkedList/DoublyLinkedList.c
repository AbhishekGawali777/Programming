#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	struct Node* ABG_pPrevNode;
	int ABG_iData;
	struct Node* ABG_pNextNode;
}NODE;

int main(void)
{
	// Function Declarations

	void ABG_Display(NODE*);
	void ABG_InsertNode(NODE**, int);
	void ABG_DeleteNode(NODE**, unsigned int);
	void ABG_InsertAtPosition(NODE**, int, unsigned int);

	// Variable Declarations

	NODE* ABG_psnFirst = NULL;
	int ABG_iNum;
	unsigned int ABG_iPosition;

	// Code

	do
	{
		printf("\n\n");

		printf("1. Insert Number\n");
		printf("2. Insert Number In Between\n");
		printf("3. Delete Number\n");
		printf("4. Exit\n");

		printf("\n\n");
		printf("Enter Choice : \t");
		fflush(stdin);
		scanf_s("%2d", &ABG_iNum);

		switch (ABG_iNum)
		{
		case 1:

			printf("Enter Number : \t");
			fflush(stdin);
			scanf_s("%d", &ABG_iNum);

			ABG_InsertNode(&ABG_psnFirst, ABG_iNum);
			ABG_Display(ABG_psnFirst);

			break;
		case 2:

			printf("Enter Number : \t");
			fflush(stdin);
			scanf_s("%d", &ABG_iNum);

			printf("Enter Position : \t");
			scanf_s("%lu", &ABG_iPosition);

			ABG_InsertAtPosition(&ABG_psnFirst, ABG_iNum, ABG_iPosition);
			ABG_Display(ABG_psnFirst);

			break;
		case 3:

			printf("Enter Position : \t");
			fflush(stdin);
			scanf_s("%lu", &ABG_iPosition);

			ABG_DeleteNode(&ABG_psnFirst, ABG_iPosition);
			ABG_Display(ABG_psnFirst);

			break;
		case 4:
			ABG_Display(ABG_psnFirst);
			printf("\n\n\t\t\t +-+-+-+-+-+-+-+ THANK YOU +-+-+-+-+-+-+-+\n\n\n\n");
			exit(0);
		default:
			printf("\n\n+-+-+-+-+-+-+-+ ENTER VALID CHOICE +-+-+-+-+-+\n\n");
			fflush(stdin);
			break;
		}
	} while (1);

	return(0);
}

void ABG_InsertNode(NODE** ABG_psnHead, int ABG_iNum)
{
	// Variable Declaration

	NODE* ABG_psnTemp = NULL;
	NODE* ABG_psnNewNode = NULL;

	// Code

	ABG_psnNewNode = (NODE*)malloc(sizeof(NODE));

	if (NULL == ABG_psnNewNode)
	{
		printf("\n\nUnable To Allocate Memory\n\n");
		return;
	}

	ABG_psnNewNode->ABG_iData = ABG_iNum;
	ABG_psnNewNode->ABG_pNextNode = NULL;
	ABG_psnNewNode->ABG_pPrevNode = NULL;

	if (NULL == *ABG_psnHead)
	{
		*ABG_psnHead = ABG_psnNewNode;
		return;
	}

	ABG_psnTemp = *ABG_psnHead;

	while (ABG_psnTemp->ABG_pNextNode)
	{
		ABG_psnTemp = ABG_psnTemp->ABG_pNextNode;
	}

	ABG_psnTemp->ABG_pNextNode = ABG_psnNewNode;
	ABG_psnNewNode->ABG_pPrevNode = ABG_psnTemp;
}

void ABG_InsertAtPosition(NODE** ABG_psnHead, int ABG_iNum, unsigned int ABG_iPosition)
{
	// Function Declaration

	unsigned int ABG_CountNode(NODE*);

	// Variable Declaration
	unsigned int ABG_uiNodeCount;
	NODE* ABG_psnNewNode = NULL;
	NODE* ABG_psnTempNode = NULL;

	// Code

	ABG_psnNewNode = (NODE*)malloc(sizeof(NODE));

	if (NULL == ABG_psnNewNode)
	{
		printf("\n\nCannot Allocate Memory..!!!\n\n");
		return;
	}

	ABG_psnNewNode->ABG_iData = ABG_iNum;
	ABG_psnNewNode->ABG_pNextNode = NULL;
	ABG_psnNewNode->ABG_pPrevNode = NULL;

	ABG_uiNodeCount = ABG_CountNode(*ABG_psnHead);

	if (ABG_iPosition == 1)
	{
		ABG_psnNewNode->ABG_pNextNode = *ABG_psnHead;
		ABG_psnNewNode->ABG_pPrevNode = NULL;
		*ABG_psnHead = ABG_psnNewNode;

		return;
	}
	else if (ABG_iPosition == ABG_uiNodeCount + 1)
	{
		free(ABG_psnNewNode);
		ABG_InsertNode(ABG_psnHead, ABG_iNum);

		return;
	}
	else if (ABG_iPosition > ABG_uiNodeCount + 1 || ABG_iPosition <= 0)
	{
		free(ABG_psnNewNode);
		ABG_psnNewNode = NULL;
		printf("\n\n+-+-+-+-+-+-+-+ ENTER VALID POSITION +-+-+-+-+-+\n\n");

		return;
	}

	ABG_psnTempNode = *ABG_psnHead;

	while (ABG_iPosition - 2 != 0)
	{
		ABG_psnTempNode = ABG_psnTempNode->ABG_pNextNode;
		ABG_iPosition--;
	}

	ABG_psnNewNode->ABG_pNextNode = ABG_psnTempNode->ABG_pNextNode;
	ABG_psnNewNode->ABG_pPrevNode = ABG_psnTempNode;
	ABG_psnNewNode->ABG_pNextNode->ABG_pPrevNode = ABG_psnNewNode;
	ABG_psnTempNode->ABG_pNextNode = ABG_psnNewNode;
}

void ABG_DeleteNode(NODE** ABG_psnHead, unsigned int ABG_iPosition)
{
	// Function Declaration 

	unsigned int ABG_CountNode(NODE*);

	// Variable Declaration
	unsigned int ABG_uiNodeCount;
	NODE* ABG_psnTempNode1 = *ABG_psnHead;
	NODE* ABG_psnTempNode2 = *ABG_psnHead;

	//Code

	ABG_uiNodeCount = ABG_CountNode(*ABG_psnHead);

	if (ABG_iPosition == 1)
	{
		if (NULL == *ABG_psnHead)
			return;

		*ABG_psnHead = ABG_psnTempNode1->ABG_pNextNode;
		free(ABG_psnTempNode1);

		ABG_psnTempNode1 = NULL;
		ABG_psnTempNode2 = NULL;

		return;
	}
	else if (ABG_iPosition == ABG_uiNodeCount)
	{
		while (ABG_psnTempNode1)
		{
			ABG_psnTempNode1 = ABG_psnTempNode1->ABG_pNextNode;

			if (ABG_psnTempNode1->ABG_pNextNode == NULL)
			{
				ABG_psnTempNode1->ABG_pPrevNode = NULL;
				break;
			}
			ABG_psnTempNode2 = ABG_psnTempNode2->ABG_pNextNode;
		}

		free(ABG_psnTempNode1);
		ABG_psnTempNode1 = NULL;

		ABG_psnTempNode2->ABG_pNextNode = NULL;

		return;
	}
	else if (ABG_iPosition > ABG_uiNodeCount || ABG_iPosition <= 0)
	{
		printf("\n\n+-+-+-+-+-+-+-+ ENTER VALID POSITION +-+-+-+-+-+\n\n");

		return;
	}

	while (ABG_iPosition - 2)
	{
		ABG_psnTempNode1 = ABG_psnTempNode1->ABG_pNextNode;
		ABG_iPosition--;
	}

	ABG_psnTempNode2 = ABG_psnTempNode1->ABG_pNextNode;
	ABG_psnTempNode1->ABG_pNextNode = ABG_psnTempNode2->ABG_pNextNode;
	ABG_psnTempNode2->ABG_pNextNode->ABG_pPrevNode = ABG_psnTempNode1;
	ABG_psnTempNode2->ABG_pNextNode = NULL;
	ABG_psnTempNode2->ABG_pPrevNode = NULL;

	free(ABG_psnTempNode2);
	ABG_psnTempNode2 = NULL;
}

void ABG_Display(NODE* ABG_psnHead)
{
	// Code 

	if (NULL == ABG_psnHead)
	{
		printf("\n\nEmpty Linked List ...!!!\n\n");
		return;
	}

	printf("\n\nLinked List Is :\t");

	while (ABG_psnHead)
	{
		printf("|%d|->", ABG_psnHead->ABG_iData);
		ABG_psnHead = ABG_psnHead->ABG_pNextNode;
	}

	printf("\n\n");
}

unsigned int ABG_CountNode(NODE* ABG_psnHead)
{
	// Variable Declaration

	unsigned int ABG_NumberOfNodes = 0;

	while (ABG_psnHead)
	{
		ABG_psnHead = ABG_psnHead->ABG_pNextNode;
		ABG_NumberOfNodes++;
	}

	return(ABG_NumberOfNodes);
}