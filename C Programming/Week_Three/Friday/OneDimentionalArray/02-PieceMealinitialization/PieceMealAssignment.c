#include <stdio.h>

int main(void)
{
	int ABG_iArrayOne[10];
	int ABG_iArrayTwo[10];

	/***** ABG_iArrayone ******/

	ABG_iArrayOne[0] = 5;
	ABG_iArrayOne[1] = 10;
	ABG_iArrayOne[2] = 15;
	ABG_iArrayOne[3] = 20;
	ABG_iArrayOne[4] = 25;
	ABG_iArrayOne[5] = 30;
	ABG_iArrayOne[6] = 35;
	ABG_iArrayOne[7] = 40;
	ABG_iArrayOne[8] = 45;
	ABG_iArrayOne[9] = 50;

	printf("Piece-meal (Hard-coded) Assignment And Display Of Elements to Array 'ABG_iArrayOne[10]': \n\n");

	printf("1st Element Of Array 'ABG_iArrayOne[]' Or Element At 0th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[0]);
	printf("2nd Element Of Array 'ABG_iArrayOne[]' Or Element At 1th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[1]);
	printf("3rd Element Of Array 'ABG_iArrayOne[]' Or Element At 2th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[2]);
	printf("4th Element Of Array 'ABG_iArrayOne[]' Or Element At 3th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[3]);
	printf("5th Element Of Array 'ABG_iArrayOne[]' Or Element At 4th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[4]);
	printf("6th Element Of Array 'ABG_iArrayOne[]' Or Element At 5th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[5]);
	printf("7th Element Of Array 'ABG_iArrayOne[]' Or Element At 6th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[6]);
	printf("8th Element Of Array 'ABG_iArrayOne[]' Or Element At 7th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[7]);
	printf("9th Element Of Array 'ABG_iArrayOne[]' Or Element At 8th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[8]);
	printf("10th Element Of Array 'ABG_iArrayOne[]' Or Element At 9th Index Of Array 'ABG_iArrayOne[]' = % d\n", ABG_iArrayOne[9]);
	
	// ****** ABG_iArrayTwo[] ******
	
	
	printf("\n\n");

	printf("Enter 1st Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[0]);
	printf("Enter 2nd Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[1]);
	printf("Enter 3rd Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[2]);
	printf("Enter 4th Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[3]);
	printf("Enter 5th Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[4]);
	printf("Enter 6th Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[5]);
	printf("Enter 7th Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[6]);
	printf("Enter 8th Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[7]);
	printf("Enter 9th Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[8]);
	printf("Enter 10th Element Of Array 'ABG_iArrayTwo[]' : ");
	scanf("%d", &ABG_iArrayTwo[9]);

	printf("\n\n");

	printf("Piece-meal (User Input) Assignment And Display Of Elements to Array 'ABG_iArrayTwo[10]' : \n\n");

	printf("1st Element Of Array 'ABG_iArrayTwo[]' Or Element At 0th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[0]);
	printf("2nd Element Of Array 'ABG_iArrayTwo[]' Or Element At 1th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[1]);
	printf("3rd Element Of Array 'ABG_iArrayTwo[]' Or Element At 2th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[2]);
	printf("4th Element Of Array 'ABG_iArrayTwo[]' Or Element At 3th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[3]);
	printf("5th Element Of Array 'ABG_iArrayTwo[]' Or Element At 4th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[4]);
	printf("6th Element Of Array 'ABG_iArrayTwo[]' Or Element At 5th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[5]);
	printf("7th Element Of Array 'ABG_iArrayTwo[]' Or Element At 6th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[6]);
	printf("8th Element Of Array 'ABG_iArrayTwo[]' Or Element At 7th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[7]);
	printf("9th Element Of Array 'ABG_iArrayTwo[]' Or Element At 8th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[8]);
	printf("10th Element Of Array 'ABG_iArrayTwo[]' Or Element At 9th Index Of Array 'ABG_iArrayTwo[]' = % d\n", ABG_iArrayTwo[9]);

	return(0);
}