#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int** ABG_piArray = NULL;
	int ABG_iNumRows, ABG_iNumCols;
	int ABG_iLoopCounter1, ABG_iLoopCounter2;

	printf("\n\n");
	printf("Enter Number Of Rows :\t");
	scanf_s("%d", &ABG_iNumRows);

	printf("\n\n");
	printf("Enter Number Of Cols:\t");
	scanf_s("%d", &ABG_iNumCols);

	printf("\n\n");
	printf("******* Memoty Allocation of 2D Integer Array *********\n\n");
	
	ABG_piArray = (int**)malloc(ABG_iNumRows * sizeof(int*));

	if (NULL == ABG_piArray)
	{
		printf("Failed To Allocate Memory To %d Rows Of 2d Integer Array..!!!\n\n", ABG_iNumRows);
		exit(0);
	}
	else
	{
		printf("************* Memory Allocation To %d Rows Of 2D Integer Array Succeeded...!!! ***********\n\n", ABG_iNumRows);
	}

	// Allocating Memory To Each Row which 1D Array Containing Consisting
	// Of Columns Which Contain The Actual Integers

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumRows; ABG_iLoopCounter1++)
	{
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_iNumCols; ABG_iLoopCounter2++)
		{
			ABG_piArray[ABG_iLoopCounter1] = (int*)malloc(ABG_iNumCols * sizeof(int));

			if (NULL == ABG_piArray[ABG_iLoopCounter1])
			{
				printf("Failed To Allocate Memory To Columns Of Row %d Of 2d Integer Array..!!!\n\n", ABG_iLoopCounter1);
				exit(0);
			}
			else
			{
				printf("Memory Allocation To Column %d Of Row %d Of 2D Integer Array Succeeded...!!!\n\n", 
					ABG_iLoopCounter2, ABG_iLoopCounter1);
			}
		}
	}


	//////////////////////////////		Assigning Values		//////////////////////////

	
	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumRows; ABG_iLoopCounter1++)
	{
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_iNumCols; ABG_iLoopCounter2++)
		{
			ABG_piArray[ABG_iLoopCounter1][ABG_iLoopCounter2] = (ABG_iLoopCounter1 + 1) * (ABG_iLoopCounter2 + 1);
		}
	}


	///////////////////////////			Displaying Values		///////////////////////////


	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumRows; ABG_iLoopCounter1++)
	{
		printf("Base Address Of Row %d : ABG_piArray[%d] = %d \t At Address : %p\n", ABG_iLoopCounter1,
						ABG_iLoopCounter1, ABG_piArray[ABG_iLoopCounter1][ABG_iLoopCounter2], 
						&ABG_piArray[ABG_iLoopCounter1]);
		
	}

	printf("\n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iNumRows; ABG_iLoopCounter1++)
	{
		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_iNumCols; ABG_iLoopCounter2++)
		{
			printf("ABG_piArray[%d][%d] = %d \t At Address : %p\n", ABG_iLoopCounter1,
				ABG_iLoopCounter2, ABG_piArray[ABG_iLoopCounter1][ABG_iLoopCounter2],
				&ABG_piArray[ABG_iLoopCounter1][ABG_iLoopCounter2]);
		}
		printf("\n");
	}


	//////////////////////////			Freeing Allocated Memory To Each Row	//////////////////////////

	for (ABG_iLoopCounter1 = (ABG_iNumRows - 1); ABG_iLoopCounter1 >= 0; ABG_iLoopCounter1--)
	{
		if (ABG_piArray[ABG_iLoopCounter1])
		{
			free(ABG_piArray[ABG_iLoopCounter1]);
			ABG_piArray[ABG_iLoopCounter1] = NULL;

			printf("Memory Allocated To Row %d Has Been Succesfully Freed...!!!\n\n", ABG_iLoopCounter1);
		}
	}

	//////////////////////////			Freeing Allocated Memory To Each 1D Array	//////////////////////////

	if (ABG_piArray)
	{
		free(ABG_piArray);
		ABG_piArray = NULL;
		printf("Memory Allocated To ABG_piArray Has Been Succesfully Freed...!!!\n\n");
	}

	return(0);
}