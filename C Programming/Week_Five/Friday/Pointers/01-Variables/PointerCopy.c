#include <stdio.h>

int main(void)
{
	int ABG_iNum;
	int	*ABG_Ptr;
	int *ABG_CopyPtr;

	ABG_iNum = 5;
	ABG_Ptr = &ABG_iNum;

	printf("\n\n*************Before ABG_CopyPtr = ABG_Ptr**************\n\n");
	printf("\t	ABG_iNum \t\t = %d\n", ABG_iNum);
	printf("\t	&ABG_iNum\t\t = %p\n", &ABG_iNum);
	printf("\t	*(&ABG_iNum)\t\t = %d\n", *(&ABG_iNum));
	printf("\t	ABG_Ptr \t\t = %p\n", ABG_Ptr);
	printf("\t	*ABG_Ptr \t\t = %d\n\n\n", *ABG_Ptr);

	ABG_CopyPtr = ABG_Ptr;

	printf("\n\n*************After ABG_CopyPtr = ABG_Ptr**************\n\n");
	printf("\t	ABG_iNum \t\t = %d\n", ABG_iNum);
	printf("\t	&ABG_iNum\t\t = %p\n", &ABG_iNum);
	printf("\t	*(&ABG_iNum)\t\t = %d\n", *(&ABG_iNum));
	printf("\t	ABG_Ptr \t\t = %p\n", ABG_Ptr);
	printf("\t	*ABG_Ptr \t\t = %d\n", *ABG_Ptr);
	printf("\t	ABG_CopyPtr \t\t = %p\n", ABG_CopyPtr);
	printf("\t	*ABG_CopyPtr \t\t = %d\n\n", *ABG_CopyPtr);


	return(0);
}