// C program... October 2, 2019

/*
Write a C program to check if y is greater than x, and z is greater
than y from three given integers x,y,z
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int x, y, z = 0;
		
	printf("Please enter First integer: ");
	scanf("%d", &x);
	
	printf("Please enter Second integer: ");
	scanf("%d", &y);
	
	printf("Please enter Third integer: ");
	scanf("%d", &z);
		
	if (((x > y) && (y > z)) || ((x > z) && (z > y)))
	{
		printf("First integer is greatest %d\n", x);
	}
	else if (((y > x) && (x > z)) || ((y > z) && (z > x)))
	{
		printf("Second integer is greatest %d\n", y);
	}else if (((z > x) && (x > y)) || ((z > y) && (y > x)))
	{
		printf("Third integer is greatest %d\n", z);
	}
	else {
		printf("Confused state attained... %d %d %d\n", x,y,z);
	}
}

/*





Write a C program to check if two or more non-negative given
integers have the same rightmost digit.
*/