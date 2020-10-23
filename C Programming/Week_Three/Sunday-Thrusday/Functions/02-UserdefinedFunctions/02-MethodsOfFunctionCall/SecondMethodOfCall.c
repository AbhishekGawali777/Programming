#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	void ABG_DisplayInformation(void);
	void ABG_FunctionCountry(void);

	ABG_DisplayInformation();
	ABG_FunctionCountry();

	return(0);
}

void ABG_DisplayInformation(void)
{
	void ABG_FunctionMy(void);
	void ABG_FunctionName(void);
	void ABG_FunctionIs(void);
	void ABG_FunctionFirstName(void);
	void ABG_FunctionMiddleName(void);
	void ABG_FunctionSurname(void);
	void ABG_FunctionAtAMC(void);


	ABG_FunctionMy();
	ABG_FunctionName();
	ABG_FunctionIs();
	ABG_FunctionFirstName();
	ABG_FunctionMiddleName();
	ABG_FunctionSurname();
	ABG_FunctionAtAMC();
}

void ABG_FunctionMy(void)
{
	printf("\n\n");
	printf("My");
}

void ABG_FunctionName(void)
{
	printf("\n\n");
	printf("Name");
}

void ABG_FunctionIs(void)
{
	printf("\n\n");
	printf("Is");
}

void ABG_FunctionFirstName(void)
{
	printf("\n\n");
	printf("Abhishek");
}

void ABG_FunctionMiddleName(void)
{
	printf("\n\n");
	printf("Balasaheb");
}

void ABG_FunctionSurname(void)
{
	printf("\n\n");
	printf("Gawali.");
}

void ABG_FunctionAtAMC(void)
{
	printf("\n\n");
	printf("Studying At ASTROMEDICOMP");
}

void ABG_FunctionCountry(void)
{
	printf("\n\n");
	printf("I live In India.");
	printf("\n\n");
}