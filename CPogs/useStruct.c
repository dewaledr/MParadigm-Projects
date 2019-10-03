// First C program... October 1st, 2019

#include <stdio.h>

struct person{
	int age;
	float weight;
};

int main(){
	struct person *personPtr;
	struct person person1;
	
	personPtr = &person1;
	
	printf("Enter age: ");
	scanf("%d", &personPtr->age);
	printf("Enter Weight: ");
	scanf("%f", &personPtr->weight);

	printf("\nAge: %d", personPtr->age);
	printf("\nWeighs: %2.2f", personPtr->weight);
}