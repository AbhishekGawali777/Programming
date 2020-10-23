#include <stdio.h>

int main(void)
{
	int ABG_i1DArray[5];
	int ABG_i2DArray[5][3];
	int ABG_i3DArray[256][256][128];

	int ABG_i2DNumberOfRows;
	int ABG_i2DNumberOfCols;

	int ABG_i3DDepth;
	int ABG_i3DNumberOfRows;
	int ABG_i3DNumberOfCols;

	printf("\n\nSize Of 1D Integer Array ABG_i1DArray = %lu\n", sizeof(ABG_i1DArray));
	printf("Number OF Elements In 1D  Integer Array 'ABG_i1DArray' = %lu\n", sizeof(ABG_i1DArray) / sizeof(int));

	ABG_i2DNumberOfRows = (sizeof(ABG_i2DArray) / sizeof(ABG_i2DArray[0]));
	ABG_i2DNumberOfCols = sizeof(ABG_i2DArray[0]) / sizeof(ABG_i2DArray[0][0]);

	printf("\n\nSize Of 2D Integer Array ABG_i2DArray = %lu\n", sizeof(ABG_i2DArray));
	printf("Number Of Rows In 2D  Integer Array 'ABG_i2DArray' = %lu\n", ABG_i2DNumberOfRows);
	printf("Number Of Columns In 2D  Integer Array 'ABG_i2DArray' = %lu\n", ABG_i2DNumberOfCols);
	printf("Number OF Elements In 2D  Integer Array 'ABG_i2DArray' = %lu\n", ABG_i2DNumberOfRows * ABG_i2DNumberOfCols);

	ABG_i3DNumberOfRows = sizeof(ABG_i3DArray) / sizeof(ABG_i3DArray[0]);
	ABG_i3DNumberOfCols = sizeof(ABG_i3DArray[0]) / sizeof(ABG_i3DArray[0][0]);
	ABG_i3DDepth = sizeof(ABG_i3DArray[0][0]) / sizeof(ABG_i3DArray[0][0][0]);

	printf("\n\nSize Of 3D Integer Array ABG_i3DArray = %u\n", sizeof(ABG_i3DArray));
	printf("Number Of Rows In 3D  Integer Array 'ABG_i3DArray' = %lu\n", ABG_i3DNumberOfRows);
	printf("Number Of Columns In 3D  Integer Array 'ABG_i3DArray' = %lu\n", ABG_i3DNumberOfCols);
	printf("Depth In 3D  Integer Array 'ABG_i3DArray' = %lu\n", ABG_i3DDepth);
	printf("Number OF Elements In 3D  Integer Array 'ABG_i3DArray' = %u\n", ABG_i3DNumberOfRows * ABG_i3DNumberOfCols * ABG_i3DDepth);

	return(0);
}