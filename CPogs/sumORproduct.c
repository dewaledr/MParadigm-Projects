// C program... October 2, 2019

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int num, sum = 0;
	double product = 1;
	
	char* choice = (char*) malloc(10 * sizeof(char));
		
	printf("Please enter a Number to compare: ");
	scanf("%d", &num);
	printf("Do you want to do product or sum? Enter P or S only:");
	scanf("%s", choice);
		
	if (strcmp(choice, "P")==0)
	{
		for(int i = 1; i<=num; i++)
		{
			product *= i;
			//printf("%d", product);
		}
	
		printf("The product of 1 to %d, is %0.0f\n", num, product);
		
	} else if (strcmp(choice, "S")==0)
	{
		for(int i = 1; i<=num; i++)
		{
			sum += i;
		}
	
		printf("The sum of 1 to %d, is %d\n", num, sum);
		
	}else 
	{
		printf("Input ERROR...Please enter uppercase P or S only...\n");
	}
	return 0;
}

/*
Write a C program to get the absolute difference between n and 51. If
n is greater than 51 return triple the absolute difference.
Write a C program to check two given integers, and return true if one
of them is 30 or if their sum is 30.
Write a C program to compute the sum of the two given integers. If
the sum is in the range 10..20 inclusive return 30
Write a C program that accept two integers and return true if either
one is 5 or their sum or difference is 5.
Write a C program to check if y is greater than x, and z is greater
than y from three given integers x,y,z
Write a C program to check if two or more non-negative given
integers have the same rightmost digit.
*/