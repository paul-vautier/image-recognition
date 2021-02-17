#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct _PGMData {
    int row;
    int col;
    int max_gray;
    int **matrix;
} PGMData;

void SkipComments(FILE *fp);
PGMData* readPGM(const char *file_name, PGMData *data);
void deallocate_dynamic_matrix(int **matrix, int row);
int **allocate_dynamic_matrix(int row, int col);
