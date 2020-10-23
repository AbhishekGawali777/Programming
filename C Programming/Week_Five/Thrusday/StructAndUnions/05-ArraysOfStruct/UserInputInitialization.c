#include <stdio.h>
#include <ctype.h>

#define ABG_NUMBER_OF_EMPLOYEES		5
#define ABG_NAME_LENGHT				100


struct ABG_Employee
{
	char ABG_cName[ABG_NAME_LENGHT];
	unsigned int ABG_uiAge;
	char ABG_cGender;
	float ABG_fSalary;
	char ABG_cMaritalStatus;
};

int main(void)
{
	void ABG_MyGetString(char[], int);

	unsigned int		ABG_uiLoopCounter;
	struct ABG_Employee ABG_EmployeeRecord[ABG_NUMBER_OF_EMPLOYEES];

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_NUMBER_OF_EMPLOYEES; ABG_uiLoopCounter++)
	{
		printf("******** Data Entry For Employee Number %d ******** \n\n", (ABG_uiLoopCounter + 1));

		printf("Enter Employee Name	:\t ");
		ABG_MyGetString(ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cName, ABG_NAME_LENGHT);

		printf("\nEnter Employee Age	:\t");
		scanf("%lu", &ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_uiAge);

		printf("\nEnter Employee Salary	 : \tRs. ");
		scanf("%f", &ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_fSalary);
	
		printf("\nEnter Employess's Gender (M/m For Male, F/f For Female) :\t");
		ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cGender = getche();
		ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cGender = toupper(ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cGender);

		printf("\nIs Employee Married.?(Y/y For Yes, N/n For No) :\t");
		ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cMaritalStatus = getche();
		ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cMaritalStatus = toupper(ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cMaritalStatus);

		printf("\n\n");
	}

	printf("\n\n******** DISPLAYING EMPLOYEE RECORDS ******** \n\n");

	for (ABG_uiLoopCounter = 0; ABG_uiLoopCounter < ABG_NUMBER_OF_EMPLOYEES; ABG_uiLoopCounter++)
	{
		printf("********  Employee Number %d ******** \n\n", (ABG_uiLoopCounter + 1));

		printf("Name					: %s\n", ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cName);
		printf("Age					: %lu years\n", ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_uiAge);
		printf("Salary					: Rs. %f\n", ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_fSalary);

		if(ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cMaritalStatus == 'Y')
			printf("Marital Status				: Married\n");
		else if(ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cMaritalStatus == 'N')
			printf("Marital Status				: Unmarried\n");
		else
			printf("Marital Status				: Invalid Data Entered\n");


		if (ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cGender == 'M')
			printf("Gender					: Male\n");
		else if(ABG_EmployeeRecord[ABG_uiLoopCounter].ABG_cGender == 'F')
			printf("Gender					: Female\n");
		else
			printf("Gender					: Invalid Data Entered\n");

		printf("\n\n");
	}

	return(0);
}


void ABG_MyGetString(char ABG_strInputString[], int ABG_SizeOfString)
{
	char ABG_cCh = '\0';
	unsigned int ABG_uiLoopCounter = 0;

	do
	{
		ABG_cCh = getch();
		ABG_strInputString[ABG_uiLoopCounter] = ABG_cCh;
		printf("%c", ABG_strInputString[ABG_uiLoopCounter]);

		ABG_uiLoopCounter++;

	} while ((ABG_cCh != '\r') && (ABG_uiLoopCounter < ABG_SizeOfString));

	if (ABG_uiLoopCounter == ABG_SizeOfString)
		ABG_strInputString[ABG_uiLoopCounter - 1] = '\0';
	else
		ABG_strInputString[ABG_uiLoopCounter] = '\0';
}