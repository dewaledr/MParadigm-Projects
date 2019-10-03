// C program... October 2, 2019

/*
Write a C program to compute the sum of the two given integers. If
the sum is in the range 10..20 inclusive return 30.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int num1, num2, ssum = 0;
	int defaulted = 30;
	
	//char* choice = (char*) malloc(10 * sizeof(char));
		
	printf("Please enter First integer: ");
	scanf("%d", &num1);
	
	printf("Please enter Second integer: ");
	scanf("%d", &num2);
	
	ssum = num1 + num2;
		
	if ((ssum >= 10) && (ssum <= 20))
	{
		printf("In range, returning %d\n", defaulted);
	}
	else{
		printf("Out of range, returning %d\n", ssum);
	}
	
}

/*



Write a C program that accept two integers and return true if either
one is 5 or their sum or difference is 5.
Write a C program to check if y is greater than x, and z is greater
than y from three given integers x,y,z
Write a C program to check if two or more non-negative given
integers have the same rightmost digit.
*/