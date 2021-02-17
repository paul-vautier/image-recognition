#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"
int main(int argc, char** argv){
  PGMData* data = malloc(sizeof(PGMData));
  readPGM("./dataset/1/single_0.pgm",data);
  for(int i = 0;i<data->row;i++){
    for(int j=0;j<data->col;j++){
      printf("%d;",data->matrix[i][j]);
    }
    printf("\n");
  }
}
