// third C program... October 1st, 2019

#include <stdio.h>

int sum(int a, int b){
	if (a == b){
		return (a+b)*3;
	}
	else{
		return (a + b);
	}
}

int main(){
	int result1 = sum(1,2);
	int result2 = sum(2,2);
	int result3 = sum(5,5);
	int result4 = sum(100,11);
	printf("\n%d \n%d \n%d \n%d\n", result1, result2, result3, result4);
}