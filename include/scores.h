#pragma once

#include<stdio.h>
#include<stdlib.h>


typedef struct{
	int score;
	char user_name[50];

}score;



void writeScore(score *pts);
void showScore(score *punt);