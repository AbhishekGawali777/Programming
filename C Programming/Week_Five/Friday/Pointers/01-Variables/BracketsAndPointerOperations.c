#include <stdio.h>

int main(void)
{
	int ABG_iNum;
	int* ABG_Ptr = NULL;
	int ABG_iAnswer;

	ABG_iNum = 5;
	ABG_Ptr = &ABG_iNum;

	printf("\n\n");
	printf("	ABG_iNum \t\t = %d\n", ABG_iNum);
	printf("	&ABG_iNum\t\t = %p\n", &ABG_iNum);
	printf("	*(&ABG_iNum)\t\t = %d\n", *(&ABG_iNum));
	printf("	ABG_Ptr \t\t = %p\n", ABG_Ptr);
	printf("	*ABG_Ptr \t\t = %d\n\n\n", *ABG_Ptr);

	printf("\n\n");
	printf(" Answer Of (ABG_Ptr + 10) = %p\n", (ABG_Ptr + 10));
	printf(" Answer Of *(ABG_Ptr + 10) = %d\n", *(ABG_Ptr + 10));
	printf(" Answer Of (*ABG_Ptr + 10) = %d\n", (*ABG_Ptr + 10));

	++* ABG_Ptr;
	printf(" Answer Of ++*ABG_Ptr = %d\n\n", *ABG_Ptr );

	return(0);
}