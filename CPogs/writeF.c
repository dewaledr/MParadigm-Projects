// First C program... October 1st, 2019

#include <stdio.h>

void printt(int times, char a){
	for(int i = 0; i < times; i++) {
		printf("%c", a);
	}
	printf("\n");
}

int main(){
	printf("Printing F in style...\n");
	printf("\n");
	printt(6, '#');
	printt(1, '#');
	printt(1, '#');
	printt(5, '#');
	printt(1, '#');
	printt(1, '#');
	printt(1, '#');
	printf("\n");
}