#include <stdio.h>

int main(void)
{
	char ABG_cArray1[] = {'T', 'A', 'L', 'K', ' ', 'I', 'S', '\0'};
	char ABG_cArray2[6] = {'C', 'H', 'E', 'A', 'P', '\0'};
	char ABG_cArray3[] = "SHOW";
	char ABG_cArray4[] = {'M', 'E', ' ', 'T', 'H', 'E', '\0'};
	char ABG_cArray5[] = "CODE...!!!";

	char ABG_cArrayWithoutNULLTerminator[] = { 'U', 'N', 'E', 'X', 'P', 'E', 'C', 'T', 'E', 'D'};

	printf("\n\n");
	printf("Size Of Character Array 'ABG_cArray1' Is : %lu\n", sizeof(ABG_cArray1));
	printf("Size Of Character Array 'ABG_cArray2' Is : %lu\n", sizeof(ABG_cArray2));
	printf("Size Of Character Array 'ABG_cArray3' Is : %lu\n", sizeof(ABG_cArray3));
	printf("Size Of Character Array 'ABG_cArray4' Is : %lu\n", sizeof(ABG_cArray4));
	printf("Size Of Character Array 'ABG_cArray5' Is : %lu\n", sizeof(ABG_cArray5));

	printf("\n\n");

	printf("Strings Are :\n\n");
	printf("ABG_cArray1 : %s\n\n", ABG_cArray1);
	printf("ABG_cArray2 : %s\n\n", ABG_cArray2);
	printf("ABG_cArray3 : %s\n\n", ABG_cArray3);
	printf("ABG_cArray4 : %s\n\n", ABG_cArray4);
	printf("ABG_cArray5 : %s\n\n", ABG_cArray5);

	printf("\n\n");
	printf("Size Of 'ABG_cArrayWithoutNULLTerminator' Is : %lu\n\n", sizeof(ABG_cArrayWithoutNULLTerminator));
	printf("ABG_cArrayWithoutNULLTerminator : %s\n\n", ABG_cArrayWithoutNULLTerminator);

	return(0);
}