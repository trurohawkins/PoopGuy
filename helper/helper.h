#ifndef HELP
#define HELP
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

void initDirections();
void freeDirections();
float randPercent();
int clamp(int, int, int);
int sign(int);
int abs(int);
#endif
