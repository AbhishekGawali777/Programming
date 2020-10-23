#include <stdio.h>

int main(void)
{
	int ABG_iArray[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

	int* ABG_iPtrArray = NULL;

	printf("\n\n");
	printf("***** USING ARRAY NAME AS A POINTER i.e : Value Of xth Element Of ABG_iArray : *(ABG_iPtrArray+ x) AND Address Of xth Element Of ABG_iArray : (ABG_iPtrArray+ x) *****\n\n");

	printf("Integer Array Elements And Addresses They Occupy Are As Follows: \n\n");

	printf("*(ABG_PtrArray + 0) = %d\t\t At Address (ABG_PtrArray + 0) : %p\n", *(ABG_iArray + 0), (ABG_iArray + 0));
	printf("*(ABG_PtrArray + 1) = %d\t\t At Address (ABG_PtrArray + 1) : %p\n", *(ABG_iArray + 1), (ABG_iArray + 1));
	printf("*(ABG_PtrArray + 2) = %d\t\t At Address (ABG_PtrArray + 2) : %p\n", *(ABG_iArray + 2), (ABG_iArray + 2));
	printf("*(ABG_PtrArray + 3) = %d\t\t At Address (ABG_PtrArray + 3) : %p\n", *(ABG_iArray + 3), (ABG_iArray + 3));
	printf("*(ABG_PtrArray + 4) = %d\t\t At Address (ABG_PtrArray + 4) : %p\n", *(ABG_iArray + 4), (ABG_iArray + 4));
	printf("*(ABG_PtrArray + 5) = %d\t\t At Address (ABG_PtrArray + 5) : %p\n", *(ABG_iArray + 5), (ABG_iArray + 5));
	printf("*(ABG_PtrArray + 6) = %d\t\t At Address (ABG_PtrArray + 6) : %p\n", *(ABG_iArray + 6), (ABG_iArray + 6));
	printf("*(ABG_PtrArray + 7) = %d\t\t At Address (ABG_PtrArray + 7) : %p\n", *(ABG_iArray + 7), (ABG_iArray + 7));
	printf("*(ABG_PtrArray + 8) = %d\t\t At Address (ABG_PtrArray + 8) : %p\n", *(ABG_iArray + 8), (ABG_iArray + 8));
	printf("*(ABG_PtrArray + 9) = %d\t\t At Address (ABG_PtrArray + 9) : %p\n", *(ABG_iArray + 9), (ABG_iArray + 9));

	ABG_iPtrArray = ABG_iArray;

	printf("***** USING POINTER NAME AS A ARRAY i.e : Value Of xth Element Of ABG_iArray : ABG_iPtrArray[x] AND Address Of xth Element Of ABG_iArray : &ABG_iPtrArray[x] *****\n\n");

	printf("Integer Array Elements And Addresses They Occupy Are As Follows: \n\n");

	printf("ABG_iPtrArray[0] = %d\t\tAt Address &ABG_iPtrArray[0] : %p\n", ABG_iPtrArray[0], &ABG_iPtrArray[0]);
	printf("ABG_iPtrArray[1] = %d\t\tAt Address &ABG_iPtrArray[1] : %p\n", ABG_iPtrArray[1], &ABG_iPtrArray[1]);
	printf("ABG_iPtrArray[2] = %d\t\tAt Address &ABG_iPtrArray[2] : %p\n", ABG_iPtrArray[2], &ABG_iPtrArray[2]);
	printf("ABG_iPtrArray[3] = %d\t\tAt Address &ABG_iPtrArray[3] : %p\n", ABG_iPtrArray[3], &ABG_iPtrArray[3]);
	printf("ABG_iPtrArray[4] = %d\t\tAt Address &ABG_iPtrArray[4] : %p\n", ABG_iPtrArray[4], &ABG_iPtrArray[4]);
	printf("ABG_iPtrArray[5] = %d\t\tAt Address &ABG_iPtrArray[5] : %p\n", ABG_iPtrArray[5], &ABG_iPtrArray[5]);
	printf("ABG_iPtrArray[6] = %d\t\tAt Address &ABG_iPtrArray[6] : %p\n", ABG_iPtrArray[6], &ABG_iPtrArray[6]);
	printf("ABG_iPtrArray[7] = %d\t\tAt Address &ABG_iPtrArray[7] : %p\n", ABG_iPtrArray[7], &ABG_iPtrArray[7]);
	printf("ABG_iPtrArray[8] = %d\t\tAt Address &ABG_iPtrArray[8] : %p\n", ABG_iPtrArray[8], &ABG_iPtrArray[8]);
	printf("ABG_iPtrArray[9] = %d\t\tAt Address &ABG_iPtrArray[9] : %p\n", ABG_iPtrArray[9], &ABG_iPtrArray[9]);

	printf("\n\n");

	return(0);
}