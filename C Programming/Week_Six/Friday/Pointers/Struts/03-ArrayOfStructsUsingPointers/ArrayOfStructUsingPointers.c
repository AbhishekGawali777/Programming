#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define ABG_NAME_LENGTH			50
#define ABG_MARITAL_STATUS		10

struct ABG_Employee
{
	char ABG_cName[ABG_NAME_LENGTH];
	unsigned int ABG_uiAge;
	char ABG_cGender;
	float ABG_fSalary;
	char ABG_cMaritalStatus;
};

int main(void)
{
	// Function Declaration

	void ABG_MyGetString(char[], int);

	// Variable Declarations

	struct ABG_Employee* ABG_pEmployee = NULL;
	int ABG_NumberOfEmployees, ABG_iLoopCounter;

	// Code

	printf("\n\nEnter Number Of Elployees Whose Details You Want To Record :\t");
	scanf_s("%d", &ABG_NumberOfEmployees);

	printf("\n\n");

	ABG_pEmployee = (struct ABG_Employee*)malloc(ABG_NumberOfEmployees * sizeof(struct ABG_Employee));

	if (NULL == ABG_pEmployee)
	{
		printf("Failed To Allocate Memory For %d Employees..!!\n\n", ABG_NumberOfEmployees);
		exit(0);
	}
	else
	{
		printf("Successfully Allocated Memory For %d Employees..!!\n\n", ABG_NumberOfEmployees);
	}

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NumberOfEmployees; ABG_iLoopCounter++)
	{
		printf("\n\n\n");

		printf("-------------- Enter Details Of %d Employee --------------\n\n", ABG_iLoopCounter + 1);

		printf("Enter Employee Name :\t");
		ABG_MyGetString(ABG_pEmployee[ABG_iLoopCounter].ABG_cName, ABG_NAME_LENGTH);

		printf("\n\n\n");
		printf("Enter Employee Age :\t");
		scanf_s("%d", &ABG_pEmployee[ABG_iLoopCounter].ABG_uiAge);
	
		printf("\n\n");
		
		printf("Enter Employee's Sex (M/m For Male, F/f For Female) : ");
		ABG_pEmployee[ABG_iLoopCounter].ABG_cGender = getch();
		printf("%c", ABG_pEmployee[ABG_iLoopCounter].ABG_cGender);
		ABG_pEmployee[ABG_iLoopCounter].ABG_cGender = toupper(ABG_pEmployee[ABG_iLoopCounter].ABG_cGender);
	
		printf("\n\n");

		printf("Enter Employee's Salary (in Indian Rupees) : ");
		scanf_s("%f", &ABG_pEmployee[ABG_iLoopCounter].ABG_fSalary);
		
		printf("\n\n");
		
		printf("Is The Employee Married? (Y/y For Yes, N/n For No) : ");
		ABG_pEmployee[ABG_iLoopCounter].ABG_cMaritalStatus = getch();
	
		printf("%c", ABG_pEmployee[ABG_iLoopCounter].ABG_cMaritalStatus);
		
		ABG_pEmployee[ABG_iLoopCounter].ABG_cMaritalStatus = toupper(ABG_pEmployee[ABG_iLoopCounter].ABG_cMaritalStatus);
	}

	printf("\n\n\n\n");
	
	printf("----------------------- DISPLAYING EMPLOYEE RECORDS ------------------\n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_NumberOfEmployees; ABG_iLoopCounter++)
	{
		printf("--------------- Employee Number %d ---------------\n\n", (ABG_iLoopCounter + 1));

		printf("Name : %s\n", ABG_pEmployee[ABG_iLoopCounter].ABG_cName);
		printf("Age : %d years\n", ABG_pEmployee[ABG_iLoopCounter].ABG_uiAge);

		if (ABG_pEmployee[ABG_iLoopCounter].ABG_cGender == 'M')
			printf("Sex : Male\n");
		else if (ABG_pEmployee[ABG_iLoopCounter].ABG_cGender == 'F')
			printf("Sex : Female\n");
		else
			printf("Sex : Invalid Data Entered\n");

		printf("Salary : Rs. %f\n", ABG_pEmployee[ABG_iLoopCounter].ABG_fSalary);

		if (ABG_pEmployee[ABG_iLoopCounter].ABG_cMaritalStatus == 'Y')
			printf("Marital Status : Married\n");
		else if (ABG_pEmployee[ABG_iLoopCounter].ABG_cMaritalStatus == 'N')
			printf("Marital Status : Unmarried\n");
		else
			printf("Marital Status : Invalid Data Entered\n");

		printf("\n\n");
	}

	if (ABG_pEmployee)
	{
		free(ABG_pEmployee);
		ABG_pEmployee = NULL;

		printf("Memory Allocated To %d Employees Is Successfully Freed...!!!\n\n\n", ABG_NumberOfEmployees);
	}

	return(0);
}

void ABG_MyGetString(char ABG_cString[], int ABG_iStringSize)
{
	// Variable Declarations

	int ABG_iLoopCounter;
	char ABG_cCh = '\0';
	
	//code

	ABG_iLoopCounter = 0;
	
	do
	{
		ABG_cCh = getch();
		ABG_cString[ABG_iLoopCounter] = ABG_cCh;
	
		printf("%c", ABG_cString[ABG_iLoopCounter]);
		
		ABG_iLoopCounter++;

	} while ((ABG_cCh != '\r') && (ABG_iLoopCounter < ABG_iStringSize));
	
	
	if (ABG_iLoopCounter == ABG_iStringSize)
		ABG_cString[ABG_iLoopCounter - 1] = '\0';
	else
		ABG_cString[ABG_iLoopCounter] = '\0';

}