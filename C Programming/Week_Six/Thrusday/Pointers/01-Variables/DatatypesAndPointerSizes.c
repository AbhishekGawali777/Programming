#include <stdio.h>

struct ABG_Employee
{
	char ABG_cName[50];
	unsigned int ABG_uiAge;
	float ABG_Salary;
	char ABG_Gender;
	char ABG_cMaritalStatus;
};

int main(void)
{
	printf("\n\n");

	printf("SIZES OF DATATYPES AND POINTERS TO THEIR RESPECTIVE DATATYPES ARE :\n\n");

	printf("Size Of (int) :\t\t%d \t\t Size Of Pointers To int (int*) :\t%d \t\t Size Of Pointer To Pointer To int(int**) :\t\t%d\n\n",
			sizeof(int), sizeof(int*), sizeof(int**));

	printf("Size Of (float) :\t%d \t\t Size Of Pointers To float(float*) :\t%d \t\t Size Of Pointer To Pointer To float(float**) :\t\t%d\n\n",
		sizeof(float), sizeof(float*), sizeof(float**));
	
	printf("Size Of (char) :\t%d \t\t Size Of Pointers To char (char*) :\t%d \t\t Size Of Pointer To Pointer To char(char**):\t\t%d\n\n",
		sizeof(char), sizeof(char*), sizeof(char**));
	
	printf("Size Of (double) :\t%d \t\t Size Of Pointers To double (double*) :\t%d \t\t Size Of Pointer To Pointer To double(double**):\t%d\n\n",
		sizeof(double), sizeof(double*), sizeof(double**));
	
	printf("Size Of (struct ABG_Employee) :\t%d \t\t Size Of Pointers To struct ABG_Employee (ABG_Employee*) :\t%d \t\t Size Of Pointer To Pointer To struct ABG_Employee(struct ABG_Employee**):\t%d\n\n",
		sizeof(struct ABG_Employee), sizeof(struct ABG_Employee*), sizeof(struct ABG_Employee**));
	return(0);
}