#include <stdio.h>

struct ABG_Employee
{
	char ABG_cName[50];
	int ABG_iAge;
	float ABG_Salary;
	char ABG_cGender;
	char ABG_cMaritalStatus;
};

int main(void)
{
	printf("\n\n");
	printf("Sizes Of Datatypes And Those Respective Poiters Are :\n\n");

	printf("Size Of(int)		: %d\t\t\t Size Of Pointer To int (int*) : %d\n\n", sizeof(int), sizeof(int*));
	printf("Size Of(char)		: %d\t\t\t Size Of Pointer To int (char*) : %d\n\n", sizeof(char), sizeof(char*));
	printf("Size Of(float)		: %d\t\t\t Size Of Pointer To int (float*) : %d\n\n", sizeof(float), sizeof(float*));
	printf("Size Of(double)		: %d\t\t\t Size Of Pointer To int (double*) : %d\n\n", sizeof(double), sizeof(double*));
	printf("Size Of(struct ABG_Employee) :%d\t\t\t Size Of Pointer To struct Employee (struct Employee*) :%d\n\n",
				sizeof(struct ABG_Employee), sizeof(struct ABG_Employee*));
	return(0);
}