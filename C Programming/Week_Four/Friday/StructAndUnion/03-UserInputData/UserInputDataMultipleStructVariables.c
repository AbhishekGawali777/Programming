#include <stdio.h>

struct ABG_MyPoint
{
	int x;
	int y;
};

int main(void)
{
	struct ABG_MyPoint ABG_PointA, ABG_PointB, ABG_PointC, ABG_PointD, ABG_PointE;

	printf("\n\n");
	
	printf("Enter X-Coordinate For Point 'ABG_PointA' :\t");
	scanf("%d", &ABG_PointA.x);

	printf("\nEnter Y-Coordinate For Point 'ABG_PointA' :\t");
	scanf("%d", &ABG_PointA.y);

	printf("\n\n");

	printf("Enter X-Coordinate For Point 'ABG_PointB' :\t");
	scanf("%d", &ABG_PointB.x);

	printf("\nEnter Y-Coordinate For Point 'ABG_PointB' :\t");
	scanf("%d", &ABG_PointB.y);

	printf("\n\n");

	printf("Enter X-Coordinate For Point 'ABG_PointC' :\t");
	scanf("%d", &ABG_PointC.x);

	printf("\nEnter Y-Coordinate For Point 'ABG_PointC' :\t");
	scanf("%d", &ABG_PointC.y);

	printf("\n\n");

	printf("Enter X-Coordinate For Point 'ABG_PointD' :\t");
	scanf("%d", &ABG_PointD.x);

	printf("\nEnter Y-Coordinate For Point 'ABG_PointD' :\t");
	scanf("%d", &ABG_PointD.y);

	printf("\n\n");

	printf("Enter X-Coordinate For Point 'ABG_PointE' :\t");
	scanf("%d", &ABG_PointE.x);

	printf("\nEnter Y-Coordinate For Point 'ABG_PointE' :\t");
	scanf("%d", &ABG_PointE.y);

	printf("\n\n");

	printf("Co-Ordinates (x, y) Of Point 'A' Are :\t(%d, %d)\n\n", ABG_PointA.x, ABG_PointA.y);
	printf("Co-Ordinates (x, y) Of Point 'B' Are :\t(%d, %d)\n\n", ABG_PointB.x, ABG_PointB.y);
	printf("Co-Ordinates (x, y) Of Point 'C' Are :\t(%d, %d)\n\n", ABG_PointC.x, ABG_PointC.y);
	printf("Co-Ordinates (x, y) Of Point 'D' Are :\t(%d, %d)\n\n", ABG_PointD.x, ABG_PointD.y);
	printf("Co-Ordinates (x, y) Of Point 'E' Are :\t(%d, %d)\n\n", ABG_PointE.x, ABG_PointE.y);


	return(0);
}