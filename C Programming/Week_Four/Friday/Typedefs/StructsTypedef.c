#include <stdio.h>

#define ABG_MAX_NAME_LENGTH  100

struct Employee
{
	char ABG_cName[ABG_MAX_NAME_LENGTH];
	unsigned int ABG_iAge;
	char ABG_cGender;
	double ABG_dSalary;
};

struct ABG_MyData
{
	int ABG_Int;
	char ABG_Char;
	float ABG_Float;
	double ABG_Double;
};

int main(void)
{
	typedef struct Employee ABG_EMPLOYEE_TYPE;
	typedef struct ABG_MyData ABG_MY_DATA_TYPE;

	struct Employee ABG_Emp = { "Sunny", 25, 'M', 18000.00 };
	ABG_EMPLOYEE_TYPE ABG_EmpTypedef = { "Bunny", 23, 'M', 21000.00 };

	struct ABG_MyData ABG_mData = {128, 'C',125.67f, 2543.0545};
	ABG_MY_DATA_TYPE ABG_mDataTypedef;

	ABG_mDataTypedef.ABG_Int = 256;
	ABG_mDataTypedef.ABG_Char = 'A';
	ABG_mDataTypedef.ABG_Float = 325.54f;
	ABG_mDataTypedef.ABG_Double = 98262.1204;

	printf("\n\n");
	printf("Structure Employee: \n\n");

	printf("ABG_Emp.ABG_cName		=%s\n", ABG_Emp.ABG_cName);
	printf("ABG_Emp.ABG_iAge		=%u\n", ABG_Emp.ABG_iAge);
	printf("ABG_Emp.ABG_cGender		=%c\n", ABG_Emp.ABG_cGender);
	printf("ABG_Emp.ABG_dSalary		=%lf\n", ABG_Emp.ABG_dSalary);

	printf("\n\n");
	printf("Structure ABG_EMPLOYEE_TYPE: \n\n");

	printf("ABG_EmpTypedef.ABG_cName		=%s\n", ABG_EmpTypedef.ABG_cName);
	printf("ABG_EmpTypedef.ABG_iAge			=%u\n", ABG_EmpTypedef.ABG_iAge);
	printf("ABG_EmpTypedef.ABG_cGender		=%c\n", ABG_EmpTypedef.ABG_cGender);
	printf("ABG_EmpTypedef.ABG_dSalary		=%lf\n", ABG_EmpTypedef.ABG_dSalary);

	printf("\n\n");
	printf("Structure ABG_mData : \n\n");

	printf("ABG_mData.ABG_Int		= %d\n", ABG_mData.ABG_Int);
	printf("ABG_mData.ABG_Char		= %c\n", ABG_mData.ABG_Char);
	printf("ABG_mData.ABG_Float		= %f\n", ABG_mData.ABG_Float);
	printf("ABG_mData.ABG_Double	= %lf\n", ABG_mData.ABG_Double);
	
	printf("\n\n");
	printf("Structure ABG_mDataT : \n\n");

	printf("ABG_mDataTypedef.ABG_Int		= %d\n", ABG_mDataTypedef.ABG_Int);
	printf("ABG_mDataTypedef.ABG_Char		= %c\n", ABG_mDataTypedef.ABG_Char);
	printf("ABG_mDataTypedef.ABG_Float		= %f\n", ABG_mDataTypedef.ABG_Float);
	printf("ABG_mDataTypedef.ABG_Double		= %lf\n", ABG_mDataTypedef.ABG_Double);

	printf("\n\n");

	return(0);
}