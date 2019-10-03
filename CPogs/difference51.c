// C program... October 2, 2019

/*
Write a C program to get the absolute difference between n and 51. If
n is greater than 51 return triple the absolute difference.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int num = 0;
	int baseNo = 51;
	
	//char* choice = (char*) malloc(10 * sizeof(char));
		
	printf("Please enter a Number to compare with 51: ");
	scanf("%d", &num);
	printf("You entered %d\n", num);
	
	int base_diff = abs(num - 51);
	
	//scanf("%s", choice);
	
	if (num > 51){
		printf("return 3 * base_diff = %d\n", 3*base_diff);
		return 3 * base_diff;
	}
	else {
		printf("return base_diff = %d\n", base_diff);
		return base_diff;
	}
}

/*

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