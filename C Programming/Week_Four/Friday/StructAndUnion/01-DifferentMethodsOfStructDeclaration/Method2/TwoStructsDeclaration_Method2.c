#include <stdio.h>

struct ABG_MyPoint
{
	int x;
	int y;
};


struct ABG_StructProperties
{
	int iQuadrant;
	char cAxisLocation[10];
};

struct ABG_MyPoint ABG_Point;
struct ABG_StructProperties ABG_PointProperties;

int main(void)
{
	printf("\n\n");

	printf("Enter X-Coordinate For A Point :\t");
	scanf("%d", &ABG_Point.x);

	printf("Enter Y-Coordinate For A Point :\t");
	scanf("%d", &ABG_Point.y);

	printf("ABG_Point Co-Ordinates (x, y) Are :\t(%d, %d)\n\n", ABG_Point.x, ABG_Point.y);

	if (ABG_Point.x == 0 && ABG_Point.y == 0)
		printf("The Point Is The Origin (%d, %d) !!!\n", ABG_Point.x, ABG_Point.y);
	else
	{
		if (ABG_Point.x == 0)
		{
			if (ABG_Point.y < 0)
				strcpy(ABG_PointProperties.cAxisLocation, "Negative Y");

			if (ABG_Point.y > 0)
				strcpy(ABG_PointProperties.cAxisLocation, "Positive Y");

			ABG_PointProperties.iQuadrant = 0;

			printf("Point Lies On %s Axis\n\n", ABG_PointProperties.cAxisLocation);
		}
		else if (ABG_Point.y == 0)
		{
			if (ABG_Point.x < 0)
				strcpy(ABG_PointProperties.cAxisLocation, "Negative X");

			if (ABG_Point.x > 0)
				strcpy(ABG_PointProperties.cAxisLocation, "Positive X");

			ABG_PointProperties.iQuadrant = 0;

			printf("Point Lies On %s Axis\n\n", ABG_PointProperties.cAxisLocation);
		}
		else
		{
			ABG_PointProperties.cAxisLocation[0] = '\0';

			if (ABG_Point.x > 0 && ABG_Point.y > 0)
				ABG_PointProperties.iQuadrant = 1;
			else if (ABG_Point.x < 0 && ABG_Point.y > 0)
				ABG_PointProperties.iQuadrant = 2;
			else if (ABG_Point.x < 0 && ABG_Point.y < 0)
				ABG_PointProperties.iQuadrant = 3;
			else
				ABG_PointProperties.iQuadrant = 4;

			printf("Point Lies In %d Quaderant Number\n\n", ABG_PointProperties.iQuadrant);
		}

	}

	return(0);
}