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
	int ABG_iNumberOfElements;
	ABG_iIntSize = sizeof(int);
	ABG_iSizeOfArray = sizeof(ABG_iArray);

	printf("Size Of Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iSizeOfArray);
	ABG_iWidth = ABG_iSizeOfArray / sizeof(ABG_iArray[0]);
	printf("Number of Rows (Width) In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iWidth);
	ABG_iHeight  = sizeof(ABG_iArray[0]) / sizeof(ABG_iArray[0][0]);
	printf("Number of Columns (Height) In Three Dimensional ( 3D ) Integer Array Is = % d\n\n", ABG_iHeight);
	
	ABG_iDepth = sizeof(ABG_iArray[0][0]) / ABG_iIntSize;
	printf("Depth In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iDepth);
	
	ABG_iNumberOfElements = ABG_iWidth * ABG_iHeight * ABG_iDepth;
	printf("Number of Elements In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", ABG_iNumberOfElements);

	printf("Elements In Integer 3D Array : \n\n");

	printf("\n********** ROW 1 ***********\n");
	printf("********** COLUMN 1 ***********\n\n");

	printf("ABG_iArray[0][0][0] = %d\n", ABG_iArray[0][0][0]);
	printf("ABG_iArray[0][0][1] = %d\n", ABG_iArray[0][0][1]);
	
	printf("********** COLUMN 2 ***********\n\n");

	printf("ABG_iArray[0][1][0] = %d\n", ABG_iArray[0][1][0]);
	printf("ABG_iArray[0][1][1] = %d\n", ABG_iArray[0][1][1]);
	
	printf("********** COLUMN 3 ***********\n\n");

	printf("ABG_iArray[0][2][0] = %d\n", ABG_iArray[0][2][0]);
	printf("ABG_iArray[0][2][1] = %d\n", ABG_iArray[0][2][1]);

	printf("\n********* ROW 2 ***********\n");
	printf("********** COLUMN 1 ***********\n\n");

	printf("ABG_iArray[1][0][0] = %d\n", ABG_iArray[1][0][0]);
	printf("ABG_iArray[1][0][1] = %d\n", ABG_iArray[1][0][1]);
	
	printf("********** COLUMN 2 ***********\n\n");

	printf("ABG_iArray[1][1][0] = %d\n", ABG_iArray[1][1][0]);
	printf("ABG_iArray[1][1][1] = %d\n", ABG_iArray[1][1][1]);

	printf("********** COLUMN 3 ***********\n\n");

	printf("ABG_iArray[1][2][0] = %d\n", ABG_iArray[1][2][0]);
	printf("ABG_iArray[1][2][1] = %d\n", ABG_iArray[1][2][1]);

	printf("\n********** ROW 3 ***********\n");
	printf("********** COLUMN 1 ***********\n\n");

	printf("ABG_iArray[2][0][0] = %d\n", ABG_iArray[2][0][0]);
	printf("ABG_iArray[2][0][1] = %d\n", ABG_iArray[2][0][1]);

	printf("********** COLUMN 2 ***********\n\n");

	printf("ABG_iArray[2][1][0] = %d\n", ABG_iArray[2][1][0]);
	printf("ABG_iArray[2][1][1] = %d\n", ABG_iArray[2][1][1]);

	printf("********** COLUMN 3 ***********\n\n");

	printf("ABG_iArray[2][2][0] = %d\n", ABG_iArray[2][2][0]);
	printf("ABG_iArray[2][2][1] = %d\n", ABG_iArray[2][2][1]);


	printf("\n********** ROW 4 ***********\n");
	printf("********** COLUMN 1 ***********\n\n");

	printf("ABG_iArray[3][0][0] = %d\n", ABG_iArray[3][0][0]);
	printf("ABG_iArray[3][0][1] = %d\n", ABG_iArray[3][0][1]);

	printf("********** COLUMN 2 ***********\n\n");

	printf("ABG_iArray[3][1][0] = %d\n", ABG_iArray[3][1][0]);
	printf("ABG_iArray[3][1][1] = %d\n", ABG_iArray[3][1][1]);

	printf("********** COLUMN 3 ***********\n\n");

	printf("ABG_iArray[3][2][0] = %d\n", ABG_iArray[3][2][0]);
	printf("ABG_iArray[3][2][1] = %d\n", ABG_iArray[3][2][1]);

	printf("\n********** ROW 5 ***********\n");
	printf("********** COLUMN 1 ***********\n\n");

	printf("ABG_iArray[4][0][0] = %d\n", ABG_iArray[4][0][0]);
	printf("ABG_iArray[4][0][1] = %d\n", ABG_iArray[4][0][1]);

	printf("********** COLUMN 2 ***********\n\n");

	printf("ABG_iArray[4][1][0] = %d\n", ABG_iArray[4][1][0]);
	printf("ABG_iArray[4][1][1] = %d\n", ABG_iArray[4][1][1]);

	printf("********** COLUMN 3 ***********\n\n");

	printf("ABG_iArray[4][2][0] = %d\n", ABG_iArray[4][2][0]);
	printf("ABG_iArray[4][2][1] = %d\n", ABG_iArray[4][2][1]);

	return(0);
}