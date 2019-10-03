// C program... October 2, 2019

/*
Write a C program that accept two integers and return true if either
one is 5 or their sum or difference is 5.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int num1, num2, ssum, sdiff = 0;
	int defaulted = 30;
	
	//char* choice = (char*) malloc(10 * sizeof(char));
		
	printf("Please enter First integer: ");
	scanf("%d", &num1);
	
	printf("Please enter Second integer: ");
	scanf("%d", &num2);
	
	ssum = num1 + num2;
	sdiff = abs(num1 - num2);
		
	if ((num1 == 5) || (num2 == 5) || (ssum == 5) || (sdiff == 5))
	{
		printf("true\n");
	}
	else{
		printf("false\n");
	}
	
}

/*




Write a C program to check if y is greater than x, and z is greater
than y from three given integers x,y,z
Write a C program to check if two or more non-negative given
integers have the same rightmost digit.
*/