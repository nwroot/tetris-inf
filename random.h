#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int randint(int lower, int upper){
	int number;
	srand(time(NULL));
	number = (rand() % (upper-lower+1)) + lower;
	//Calculates range and sums to make it fit
	return number;
}