#ifndef HELP
#define HELP
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include<string.h>
#include <math.h>
#include "list.h"
//#include "file.h"

void initDirections();
void freeDirections();
int **getDirs();
int **getDir8();
float getAngle(int dir);
int convertInvert(bool inv);
float randPercent();
int randomInt(int upper);
int clamp(int, int, int);
float max(float a, float b);
float min(float a, float b);
int sign(int);
int abs(int);
char *fileToString(char *txt);
bool strCompare(char *str1, char *str2);
void printArray(int**, int, int);
bool compareColor(void *c1, void *c2);
int decPlace(int d);
#endif
