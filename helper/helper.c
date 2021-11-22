#include "helper.h"
#include "list.c"
//#include "file.c"
int **dirs;

void initDirections() {
	dirs = (int**)calloc(4, sizeof(int*));
	for (int i = 0; i < 4; i++) {
		dirs[i] = (int*)calloc(2, sizeof(int));
	}
	dirs[0][0] = 0;
	dirs[0][1] = 1;
	dirs[1][0] = -1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = -1;
	dirs[3][0] = 1;
	dirs[3][1] = 0;
}

void freeDirections() {
	for (int i = 0; i < 4; i++) {
		free(dirs[i]);
	}
	free(dirs);
}

int **getDirs() {
	return dirs;
}

float randPercent() {
	return (float)rand()/(float)(RAND_MAX);
}

int clamp(int val, int min, int max) {
	if (min < max) {
		if (val < min) {
			return min;
		}	else if (val > max) {
			return max;
		} else {
			return val;
		}
	} else {
		return val;
	}
}

int sign(int num) {
	if (num > 0) {
		return 1;
	} else if (num < 0) {
		return -1;
	} else {
		return 0;
	}
}

int abs(int num) {
	if (num < 0) {
		return num * -1;
	} else {
		return num;
	}
}

char *fileToString(char *txt)
{
	FILE *fptr;
	int n = 0;
	int c;

	fptr = fopen(txt, "r");
	char *t = NULL;
	if (fptr != NULL) {
		fseek(fptr, 0, SEEK_END);
		long fSize = ftell(fptr);
		printf("file size: %i\n", fSize);
		fseek(fptr, 0, SEEK_SET);
		t = (char*)malloc(fSize * sizeof(char));
		while ((c = fgetc(fptr)) != EOF) {
			t[n++] = (char)c;
		}
		printf("wrote into: %i\n", n);
		t[fSize-1] = '\0';
		fseek(fptr, 0, SEEK_SET);
		fclose(fptr);
	}
	return t;
}

bool strCompare(char *str1, char *str2) {
	while (*str1 != '\0') {
		if (*str1 != *str2) {
			return false;
		}
		str1++;
		str2++;
	}
	return true;
}

void printArray(int **array, int sizeX, int sizeY) {
	printf("\n");

   for( int  y=sizeY-1;y>-1;y--) {
      for(int x=0; x<sizeX; x++) {
         printf("%d ", array[x][y]);
		 if( array[x][y] == 0){
			 printf(" ");
		 }
         if(x==sizeX-1){
            printf("\n");
         }
      }
   }
}
