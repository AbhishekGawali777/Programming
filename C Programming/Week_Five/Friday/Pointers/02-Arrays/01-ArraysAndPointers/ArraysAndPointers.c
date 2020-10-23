#include <stdio.h>

int main(void)
{
	int ABG_iArray[] = { 23, 125, 98, 124, 55, 63, 47, 82, 99, 73 };
	float ABG_fArray[] = { 9.8f, 8.7f, 7.6f, 6.5f, 5.4f };
	double ABG_dArray[] = { 12.365, 3643.87894,  5465.13251 };
	char ABG_cArray[] = { 'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P', '\0' };

	printf("\n\n");

	printf("Integer Array Elements And Addresses They Occupy Are As Follows: \n\n");

	printf("ABG_iArray[0] = %d At Address : %p\n", *(ABG_iArray + 0), (ABG_iArray + 0));
	printf("ABG_iArray[1] = %d At Address : %p\n", *(ABG_iArray + 1), (ABG_iArray + 1));
	printf("ABG_iArray[2] = %d At Address : %p\n", *(ABG_iArray + 2), (ABG_iArray + 2));
	printf("ABG_iArray[3] = %d At Address : %p\n", *(ABG_iArray + 3), (ABG_iArray + 3));
	printf("ABG_iArray[4] = %d At Address : %p\n", *(ABG_iArray + 4), (ABG_iArray + 4));
	printf("ABG_iArray[5] = %d At Address : %p\n", *(ABG_iArray + 5), (ABG_iArray + 5));
	printf("ABG_iArray[6] = %d At Address : %p\n", *(ABG_iArray + 6), (ABG_iArray + 6));
	printf("ABG_iArray[7] = %d At Address : %p\n", *(ABG_iArray + 7), (ABG_iArray + 7));
	printf("ABG_iArray[8] = %d At Address : %p\n", *(ABG_iArray + 8), (ABG_iArray + 8));
	printf("ABG_iArray[9] = %d At Address : %p\n", *(ABG_iArray + 9), (ABG_iArray + 9));
	
	printf("\n\n");

	printf("Float Array Elements And Addresses They Occupy Are As Follows: \n\n");
	printf("ABG_fArray[0] = %f At Address : %p\n", *(ABG_fArray + 0), (ABG_fArray + 0));
	printf("ABG_fArray[1] = %f At Address : %p\n", *(ABG_fArray + 1), (ABG_fArray + 1));
	printf("ABG_fArray[2] = %f At Address : %p\n", *(ABG_fArray + 2), (ABG_fArray + 2));
	printf("ABG_fArray[3] = %f At Address : %p\n", *(ABG_fArray + 3), (ABG_fArray + 3));
	printf("ABG_fArray[4] = %f At Address : %p\n", *(ABG_fArray + 4), (ABG_fArray + 4));
	
	printf("\n\n");

	printf("Double Array Elements And Addresses They Occupy Are As Follows: \n\n");
	printf("ABG_dArray[0] = %lf At Address : %p\n", *(ABG_dArray + 0), (ABG_dArray + 0));
	printf("ABG_dArray[1] = %lf At Address : %p\n", *(ABG_dArray + 1), (ABG_dArray + 1));
	printf("ABG_dArray[2] = %lf At Address : %p\n", *(ABG_dArray + 2), (ABG_dArray + 2));

	printf("\n\n");
	
	printf("ABG_cArray[0]  = %c At Address : %p\n", *(ABG_cArray + 0), (ABG_cArray + 0));
	printf("ABG_cArray[1]  = %c At Address : %p\n", *(ABG_cArray + 1), (ABG_cArray + 1));
	printf("ABG_cArray[2]  = %c At Address : %p\n", *(ABG_cArray + 2), (ABG_cArray + 2));
	printf("ABG_cArray[3]  = %c At Address : %p\n", *(ABG_cArray + 3), (ABG_cArray + 3));
	printf("ABG_cArray[4]  = %c At Address : %p\n", *(ABG_cArray + 4), (ABG_cArray + 4));
	printf("ABG_cArray[5]  = %c At Address : %p\n", *(ABG_cArray + 5), (ABG_cArray + 5));
	printf("ABG_cArray[6]  = %c At Address : %p\n", *(ABG_cArray + 6), (ABG_cArray + 6));
	printf("ABG_cArray[7]  = %c At Address : %p\n", *(ABG_cArray + 7), (ABG_cArray + 7));
	printf("ABG_cArray[8]  = %c At Address : %p\n", *(ABG_cArray + 8), (ABG_cArray + 8));
	printf("ABG_cArray[9]  = %c At Address : %p\n", *(ABG_cArray + 9), (ABG_cArray + 9));
	printf("ABG_cArray[10] = %c At Address : %p\n", *(ABG_cArray + 10), (ABG_cArray + 10));
	printf("ABG_cArray[11] = %c At Address : %p\n", *(ABG_cArray + 11), (ABG_cArray + 11));
	printf("ABG_cArray[12] = %c At Address : %p\n", *(ABG_cArray + 12), (ABG_cArray + 12));
	printf("ABG_cArray[13] = %c At Address : %p\n", *(ABG_cArray + 13), (ABG_cArray + 13));

	printf("\n\n");

	return(0);
}