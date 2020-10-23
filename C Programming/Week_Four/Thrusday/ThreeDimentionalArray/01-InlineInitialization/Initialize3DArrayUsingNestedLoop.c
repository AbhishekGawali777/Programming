#include <stdio.h>

int main(void)
{
	int ABG_iArray[5][3][2] = { { {101, 102}, {103, 104}, {105, 106} },
								{ {107, 108}, {109, 110}, {15, 16} },
								{ {48, 53}, {58, 44}, {25, 23} },
								{ {152, 523}, { 528, 414 }, { 245, 263 } },
								{ {483, 553}, {958, 474}, {253, 233} } };

	int ABG_iWidth;
	int ABG_iDepth;
	int ABG_iHeight;
	int ABG_iIntSize;
	int ABG_iSizeOfArray;
	int ABG_iLoopCounter1;
	int ABG_iLoopCounter2;
	int ABG_iLoopCounter3;
	int ABG_iNumberOfElements;
	ABG_iIntSize = sizeof(int);
	ABG_iSizeOfArray = sizeof(ABG_iArray);

	printf("Size Of Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iSizeOfArray);
	ABG_iWidth = ABG_iSizeOfArray / sizeof(ABG_iArray[0]);
	printf("Number of Rows (Width) In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iWidth);
	ABG_iHeight = sizeof(ABG_iArray[0]) / sizeof(ABG_iArray[0][0]);
	printf("Number of Columns (Height) In Three Dimensional ( 3D ) Integer Array Is = % d\n\n", ABG_iHeight);

	ABG_iDepth = sizeof(ABG_iArray[0][0]) / ABG_iIntSize;
	printf("Depth In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iDepth);

	ABG_iNumberOfElements = ABG_iWidth * ABG_iHeight * ABG_iDepth;
	printf("Number of Elements In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iNumberOfElements);

	printf("Elements In Integer 3D Array : \n\n");

	for (ABG_iLoopCounter1 = 0; ABG_iLoopCounter1 < ABG_iWidth; ABG_iLoopCounter1++)
	{
		printf("\n********** ROW %d ***********\n", ABG_iLoopCounter1 + 1);

		for (ABG_iLoopCounter2 = 0; ABG_iLoopCounter2 < ABG_iHeight; ABG_iLoopCounter2++)
		{
			printf("\n********** COLUMN %d ***********\n", ABG_iLoopCounter2 + 1);

			for (ABG_iLoopCounter3 = 0; ABG_iLoopCounter3 < ABG_iDepth; ABG_iLoopCounter3++)
			{
				printf("ABG_iArray[%d][%d][%d] = %d\n", ABG_iLoopCounter1, ABG_iLoopCounter2, ABG_iLoopCounter3, ABG_iArray[ABG_iLoopCounter1][ABG_iLoopCounter2][ABG_iLoopCounter3]);
			}
			printf("\n\n");
		}
		printf("\n\n");
	}

	return(0);
}