#include <stdio.h>


int main(void)
{
	struct ABG_MyRectangle
	{
		struct ABG_MyPoint
		{
			int x;
			int y;
		} ABG_pPoint1, ABG_pPoint2;
	
	} ABG_Rect = { {65, 18}, {78, 32} };

	int ABG_iLength, ABG_iBreadth, ABG_iArea;

	ABG_iLength = ABG_Rect.ABG_pPoint2.y - ABG_Rect.ABG_pPoint1.y;
	if (ABG_iLength < 0)
		ABG_iLength = ABG_iLength * -1;

	ABG_iBreadth = ABG_Rect.ABG_pPoint2.x - ABG_Rect.ABG_pPoint1.x;
	if (ABG_iBreadth < 0)
		ABG_iBreadth = ABG_iBreadth * -1;

	ABG_iArea = ABG_iLength * ABG_iBreadth;

	printf("\n\n");
	printf("Length Of Rectangle = %d\n", ABG_iLength);
	printf("Breadth Of Rectangle = %d\n", ABG_iBreadth);
	printf("Area Of Rectangle = %d\n", ABG_iArea);

	return(0);
}