#include <stdio.h>

int main(void)
{
	int ABG_IntSize;
	int ABG_iArraySize;
	int ABG_iNumberOfRows;
	int ABG_iNumberOfCols;
	int ABG_iNumberOfElements;
	
	int ABG_iArray[5][3] = { {1, 2, 3}, {5, 7, 9}, {4, 6, 8}, {11, 13, 16}, {21, 24, 29} };

	ABG_IntSize = sizeof(int);

	ABG_iArraySize = sizeof(ABG_iArray);
	printf("\n\nSize Of Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iArraySize);

	ABG_iNumberOfRows = ABG_iArraySize / sizeof(ABG_iArray[0]);
	printf("\n\nNumber Of Rows In Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iNumberOfRows);

	ABG_iNumberOfCols = sizeof(ABG_iArray[0]) / sizeof(ABG_iArray[0][0]); // OR sizeof(ABG_iArray[0]) / ABG_IntSize;
	printf("\n\nNumber Of Columns In Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iNumberOfCols);

	ABG_iNumberOfElements = ABG_iNumberOfRows * ABG_iNumberOfCols;
	printf("\n\nNumber Of Elements In Two Dimensional (2D) Integer Array Is : %d\n\n", ABG_iNumberOfElements);

	printf("\n\n");
	printf("Elements In 2D Array Are : \n\n");

	printf("\t******** ROW 1 *********\n\n");
	printf("\tABG_iArray[0][0] = %d\n", ABG_iArray[0][0]);
	printf("\tABG_iArray[0][1] = %d\n", ABG_iArray[0][1]);
	printf("\tABG_iArray[0][2] = %d\n\n", ABG_iArray[0][2]);

	printf("\t******** ROW 2 *********\n\n");
	printf("\tABG_iArray[1][0] = %d\n", ABG_iArray[1][0]);
	printf("\tABG_iArray[1][1] = %d\n", ABG_iArray[1][1]);
	printf("\tABG_iArray[1][2] = %d\n\n", ABG_iArray[1][2]);

	printf("\t******** ROW 3 *********\n\n");
	printf("\tABG_iArray[2][0] = %d\n", ABG_iArray[2][0]);
	printf("\tABG_iArray[2][1] = %d\n", ABG_iArray[2][1]);
	printf("\tABG_iArray[2][2] = %d\n\n", ABG_iArray[2][2]);

	printf("\t******** ROW 4 *********\n\n");
	printf("\tABG_iArray[3][0] = %d\n", ABG_iArray[3][0]);
	printf("\tABG_iArray[3][1] = %d\n", ABG_iArray[3][1]);
	printf("\tABG_iArray[3][2] = %d\n\n", ABG_iArray[3][2]);

	printf("\t******** ROW 5 *********\n\n");
	printf("\tABG_iArray[4][0] = %d\n", ABG_iArray[4][0]);
	printf("\tABG_iArray[4][1] = %d\n", ABG_iArray[4][1]);
	printf("\tABG_iArray[4][2] = %d\n\n", ABG_iArray[4][2]);

	printf("\n\n");

	return(0);
}