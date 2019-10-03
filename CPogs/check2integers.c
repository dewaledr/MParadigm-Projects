// C program... October 2, 2019

/*
Write a C program to check two given integers, and return true if one
of them is 30 or if their sum is 30.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int num1, num2 = 0;
	
	//char* choice = (char*) malloc(10 * sizeof(char));
		
	printf("Please enter First Number to compare: ");
	scanf("%d", &num1);
	
	printf("Please enter Second Number to compare: ");
	scanf("%d", &num2);
	
// 	printf("Do you want to do product or sum? Enter P or S only:");
// 	scanf("%s", choice);
		
	if ((num1 == 30) || (num2 == 30) || (num1 + num2 == 30))
	{
		printf("True\n");
	}
	else{
		printf("False\n");
	}
	
}

/*


Write a C program to compute the sum of the two given integers. If
the sum is in the range 10..20 inclusive return 30
Write a C program that accept two integers and return true if either
one is 5 or their sum or difference is 5.
Write a C program to check if y is greater than x, and z is greater
than y from three given integers x,y,z
Write a C program to check if two or more non-negative given
integers have the same rightmost digit.
*/