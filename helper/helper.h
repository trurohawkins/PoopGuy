#ifndef HELP
#define HELP
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include <math.h>
#include "list.h"
//#include "file.h"

void initDirections();
void freeDirections();
int **getDirs();
float randPercent();
int clamp(int, int, int);
int sign(int);
int abs(int);
//float fabs(float);
char *fileToString(char *txt);
bool strCompare(char *str1, char *str2);
#endif
