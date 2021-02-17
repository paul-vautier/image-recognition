#include "recognition.h"

int compare_two(const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void median_filter(PGMData* data){
  int* new_matrix[data->row];
  for(int i = 0;i<data->row;i++){
    if(i==0 || i == data->row -1){
      new_matrix[i]=data->matrix[i];
      continue;
    }
    new_matrix[i]=malloc(data->col*sizeof(int));
    for(int j = 0;j<data->col;j++){
      if(j ==0 || j == data->col-1){
        new_matrix[i][j] = data->matrix[i][j];
        continue;
      }
      int median[8];
      median[0] = data->matrix[i-1][j-1];
      median[1] = data->matrix[i][j-1];
      median[2] = data->matrix[i+1][j-1];

      median[3] = data->matrix[i-1][j];
      median[4] = data->matrix[i+1][j];

      median[5] = data->matrix[i-1][j+1];
      median[6] = data->matrix[i][j+1];
      median[7] = data->matrix[i+1][j+1];

      qsort(median,sizeof(median)/sizeof(*median),sizeof(*median),compare_two);

      if(data->matrix[i][j] > median[7] || data->matrix[i][j] < median[0]){
        new_matrix[i][j] = median[4];
      }
    }
  }
  data->matrix = new_matrix;
}

void binary_floor(PGMData* data,int floor){
    for(int i = 0;i<data->row;i++){
      for(int j = 0;j<data->col;j++){
        if(data->matrix[i][j] < floor)
          data->matrix[i][j] = 0;
        else
          data->matrix[i][j] = 255;
      }
    }
}
