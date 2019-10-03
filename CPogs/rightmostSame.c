// C program... October 2, 2019

/*
Write a C program to check if two or more non-negative given
integers have the same rightmost digit.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int x, y, z = 0;
		
	printf("Please enter First non-negative integer: ");
	scanf("%d", &x);
	
	printf("Please enter Second non-negative integer: ");
	scanf("%d", &y);
	
	int rem1 = x%100;
	int rem2 = y%100;
		
	if (rem1%10 == rem2%10)
	{
		printf("Yes they do have same rightmost digit! %d %d\n", x, y);
	}
	else 
	{
		printf("Nope, they do not have same rightmost digit! %d %d\n", x, y);
	}
}






