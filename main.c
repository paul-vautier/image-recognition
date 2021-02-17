#include <stdio.h>
#include <stdlib.h>
#include "recognition.h"
int main(int argc, char** argv){
  PGMData* data = malloc(sizeof(PGMData));
  readPGM("./dataset/4/multiple_4.pgm",data);
  median_filter(data);
  binary_floor(data,50);
  writePGM("rewritten2.pgm",data);
}
