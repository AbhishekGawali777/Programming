#include <stdio.h>

struct ABG_MyPoint
{
	int x;
	int y;
}ABG_PointA, ABG_PointB, ABG_PointC, ABG_PointD, ABG_PointE;


int main(void)
{
	ABG_PointA.x = 12;
	ABG_PointA.y = 16;

	ABG_PointB.x = 5;
	ABG_PointB.y = 0;
	
	ABG_PointC.x = 15;
	ABG_PointC.y = 7;
	
	ABG_PointD.x = 9;
	ABG_PointD.y = 21;
	
	ABG_PointE.x = 56;
	ABG_PointE.y = 34;
	
	printf("\n\n");
	printf("Co-Ordinates (x, y) Of Point 'A' Are :\t(%d, %d)\n\n", ABG_PointA.x, ABG_PointA.y);
	printf("Co-Ordinates (x, y) Of Point 'B' Are :\t(%d, %d)\n\n", ABG_PointB.x, ABG_PointB.y);
	printf("Co-Ordinates (x, y) Of Point 'C' Are :\t(%d, %d)\n\n", ABG_PointC.x, ABG_PointC.y);
	printf("Co-Ordinates (x, y) Of Point 'D' Are :\t(%d, %d)\n\n", ABG_PointD.x, ABG_PointD.y);
	printf("Co-Ordinates (x, y) Of Point 'E' Are :\t(%d, %d)\n\n", ABG_PointE.x, ABG_PointE.y);


	return(0);
}