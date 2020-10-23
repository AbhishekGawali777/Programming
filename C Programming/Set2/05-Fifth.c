#include <stdio.h>

int main(int argc, char* argv[])
{
	int ABG_Choice = 0;

	void ABG_FahrenheitToCelcius(int, int, int);

	do
	{
		printf("\nEnter 1 to print Fahrenheit to Celcius Table from  0 to 10 in step of 1");
		printf("\nEnter 2 to print Fahrenheit to Celcius Table from  0 to 20 in step of 5");
		printf("\nEnter 3 to print Fahrenheit to Celcius Table from 10 to 50 in step of 10");
		printf("\nEnter 0 to Exit\n");

		printf("\nPlease Enter Choice :\t");
		fflush(stdin);
		scanf("%1d", &ABG_Choice);
		
		printf("\n\n ---------------- Fahrenheit To Celcius Table ---------------\n\n");

		switch (ABG_Choice)
		{
		case 1:
			ABG_FahrenheitToCelcius(0, 10, 1);
			break;
		case 2:
			ABG_FahrenheitToCelcius(0, 20, 5);
			break;
		case 3:
			ABG_FahrenheitToCelcius(10, 50, 10);
			break;
		default:
			printf("\n! -- Enter Valid Choice -- !");
		}
	} while (ABG_Choice > 0);
	
	return(0);
}

void ABG_FahrenheitToCelcius(int ABG_LowerLimit, int ABG_UpperLimit, int ABG_Step)
{
	int ABG_Fahrenheit = -1;

	for (ABG_Fahrenheit = ABG_LowerLimit; ABG_Fahrenheit <= ABG_UpperLimit; ABG_Fahrenheit = ABG_Fahrenheit + ABG_Step)
	{
		printf("\t\t%3d\t\t%6.1f\n", ABG_Fahrenheit, ((5.0 / 9.0) * (ABG_Fahrenheit - 32)));
		
	}
}