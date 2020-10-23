#include <stdio.h>

#define ABG_NAME_LENGTH			100
#define ABG_MARITAL_STATUS		10
#define ABG_EMPLOYEE_RECORDS	5
struct ABG_Employee
{
	char ABG_cName[ABG_NAME_LENGTH];
	unsigned int ABG_uiAge;
	float ABG_fSalary;
	char ABG_cGender;
	char ABG_strMaritalStatus[ABG_MARITAL_STATUS];
};

int main(void)
{
	int	 ABG_iLoopCounter;
	char ABG_EmployeeAmit[]		= "Amit";
	char ABG_EmployeeAbhishek[] = "Abhishek";
	char ABG_EmployeeAnand[]	= "Anand";
	char ABG_EmployeeShivaji[]	= "Shivaji";
	char ABG_EmployeeSneha[]	= "Sneha";
	
	struct ABG_Employee ABG_EmployeeRecord[ABG_EMPLOYEE_RECORDS];

	strcpy(ABG_EmployeeRecord[0].ABG_cName, ABG_EmployeeAmit);
	ABG_EmployeeRecord[0].ABG_uiAge = 32;
	ABG_EmployeeRecord[0].ABG_cGender = 'M';
	ABG_EmployeeRecord[0].ABG_fSalary = 240500;
	strcpy(ABG_EmployeeRecord[0].ABG_strMaritalStatus, "Married");

	strcpy(ABG_EmployeeRecord[1].ABG_cName, ABG_EmployeeAbhishek);
	ABG_EmployeeRecord[1].ABG_uiAge = 22;
	ABG_EmployeeRecord[1].ABG_cGender = 'M';
	ABG_EmployeeRecord[1].ABG_fSalary = 11500;
	strcpy(ABG_EmployeeRecord[1].ABG_strMaritalStatus, "Unmarried");

	strcpy(ABG_EmployeeRecord[2].ABG_cName, ABG_EmployeeAnand);
	ABG_EmployeeRecord[2].ABG_uiAge = 35;
	ABG_EmployeeRecord[2].ABG_cGender = 'M';
	ABG_EmployeeRecord[2].ABG_fSalary = 185900;
	strcpy(ABG_EmployeeRecord[2].ABG_strMaritalStatus, "Married");

	strcpy(ABG_EmployeeRecord[3].ABG_cName, ABG_EmployeeShivaji);
	ABG_EmployeeRecord[3].ABG_uiAge = 34;
	ABG_EmployeeRecord[3].ABG_cGender = 'M';
	ABG_EmployeeRecord[3].ABG_fSalary = 238500;
	strcpy(ABG_EmployeeRecord[3].ABG_strMaritalStatus, "Married");

	strcpy(ABG_EmployeeRecord[4].ABG_cName, ABG_EmployeeSneha);
	ABG_EmployeeRecord[4].ABG_uiAge = 28;
	ABG_EmployeeRecord[4].ABG_cGender = 'F';
	ABG_EmployeeRecord[4].ABG_fSalary = 40500;
	strcpy(ABG_EmployeeRecord[4].ABG_strMaritalStatus, "Unmarried");

	printf("\n\n");
	printf("************ Displaying Employee Records ************\n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_EMPLOYEE_RECORDS; ABG_iLoopCounter++)
	{
		printf("********  Employee Number %d ******** \n\n", (ABG_iLoopCounter + 1));

		printf("Name					: %s\n", ABG_EmployeeRecord[ABG_iLoopCounter].ABG_cName);
		printf("Age					: %lu years\n", ABG_EmployeeRecord[ABG_iLoopCounter].ABG_uiAge);
		printf("Salary					: Rs. %f\n", ABG_EmployeeRecord[ABG_iLoopCounter].ABG_fSalary);
		printf("Marital Status				: %s\n", ABG_EmployeeRecord[ABG_iLoopCounter].ABG_strMaritalStatus);

		if (ABG_EmployeeRecord[ABG_iLoopCounter].ABG_cGender == 'M' ||
			ABG_EmployeeRecord[ABG_iLoopCounter].ABG_cGender == 'm')
			printf("Gender					: Male\n", ABG_EmployeeRecord[ABG_iLoopCounter].ABG_cGender);
		else
			printf("Gender					: Female\n", ABG_EmployeeRecord[ABG_iLoopCounter].ABG_cGender);

		printf("\n\n");
	}

}