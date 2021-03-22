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
    printf("i=%d / j=%d\n",data->row, data->col);
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
            new_matrix[i][j] = median[4];
        }
    }
    data->matrix = new_matrix;
}

void binary_floor(PGMData* data,int floor){
    for(int i = 0;i<data->row;i++){
        for(int j = 0;j<data->col;j++){
            if(data->matrix[i][j] < floor)
            data->matrix[i][j] = FULL;
            else
            data->matrix[i][j] = EMPTY;
        }
    }
}
Path* compute_path(PGMData* data){
    int i;
    int j;
    Path* base = init_path(data,&i,&j);
    Path* current;
    //First and last full pixel seen in a row;
    int first_full;
    int last_full;
    if(base!= NULL){
        if(j==data->col-1){
            i++;
            j=0;
        }
        current = base;
        for(i;i<data->row;i++){
            first_full = -1;
            last_full = -1;
            for(j;j<data->row;j++){
                if(data->matrix[i][j] == FULL){
                    if(first_full == -1)
                        first_full = j;
                    else
                        last_full = j;
                }
            }
            for(int k = first_full; k<=last_full;k++){
                current->next = (Path*)malloc(sizeof(Path));
                current = current->next;
                Vector2 pos = {i,k};
                current->pos = pos;
                current->val = data->matrix[i][k];
            }
            j=0;
        }
    }
    return base;
}

Path* init_path(PGMData* data, int* i, int *j){
    Path* base;
    for((*i) = 0;*i<data->row; (*i)++){
        for((*j) = 0;*j<data->col; (*j)++){
            if(data->matrix[*i][*j] == FULL){
                base = (Path*)malloc(sizeof(Path));
                Vector2 pos = {*i,*j};
                base->pos = pos;
                base->val = FULL;
                return base;
            }
        }
    }
    return NULL;
}

bool verify_image(PGMData* data,Path* model,bool with_reporting){
    Path* current;
    int size = 10;
    int indexBox = -1;
    BoundingBox boxes[size];
    bool accepted = true;
    int correct_pieces = 0;
    int incorrect_pieces = 0;
    for(int i=0;i<data->row-64;i+=6){
        for(int j=0;j<data->col-64;j+=2){
            bool in_boxes;
            do{
                in_boxes=false;
                for(int k=0;k<=indexBox;k++){
                    if(in(boxes[k],j,i)){
                        j=boxes[k].end.x+1;
                        in_boxes=true;
                    }
                }
            }while(in_boxes);

            if(data->matrix[i][j] == FULL){
                current = model;
                BoundingBox box = get_bounding_box(data,j,i);
                int bad = 0;
                while(current!=NULL){
                    if(data->matrix[box.begin.y + current->pos.y][box.begin.x + current->pos.x] != current->val){
                        bad++;
                    }
                    current = current->next;
                }
                indexBox++;
                boxes[indexBox] = box;
                if(bad>4){
                    if(with_reporting){
                        printf("Erreur sur la rondelle dans la zone x1=%d / y1=%d / x2 = %d / y2 = %d\n", box.begin.x, box.begin.y, box.end.x, box.end.y);
                        incorrect_pieces++;
                    }
                    accepted = false;
                }else if(with_reporting){
                    fprintf(stderr,"Piece correcte ++");
                    correct_pieces++;
                }
            }
        }
    }
    if(with_reporting){
        printf("\nRésultat de rapport :, %d rondelles correctes, %d rondelles incorrectes\n",correct_pieces, incorrect_pieces);
    }
    return accepted;
}
int in(BoundingBox box, int x, int y){
    return box.begin.x <= x && box.end.x >= x && box.begin.y <= y && box.end.y >= y;
}
BoundingBox get_mono_bounding(PGMData* data){
    for(int i=0;i<data->row;i+=6){
        for(int j=0;j<data->col;j+=2){
            if(data->matrix[i][j] == FULL){
                return get_bounding_box(data,j,i);
            }
        }
    }
}
Vector2 get_min_y_position(PGMData* data,int px, int py){
    //Je cherche la plus grande valeur au dessus de moi
    while(py >0 && data->matrix[py-1][px]!=EMPTY){
        py--;
    }
    //Je cherche la plus grande valeur à ma droite (car on touche toujours le cercle depuis la droite)
    int temp_y = py;
    int temp_x = px;
    while(temp_x>0 && temp_y>0 && (data->matrix[temp_y-1][temp_x]!=EMPTY || data->matrix[temp_y][temp_x+1] != EMPTY)){
        if(data->matrix[temp_y-1][temp_x]!=EMPTY){
            temp_y--;
        }else if(data->matrix[temp_y-1][temp_x+1]!=EMPTY){
            temp_y--;
            temp_x++;
        }
        else{
            temp_x++;
        }
    }
    Vector2 pos = {temp_x,temp_y};
    return pos;
}
Vector2 get_min_x_position(PGMData* data,int px, int py){
    //Je cherche la plus grande valeur au dessus de moi
    while(py >0 && data->matrix[py][px-1]!=EMPTY){
        px--;
    }
    //Je cherche la plus grande valeur de gauche depuis le haut
    //L'incrément est plus petit que la moitié du cercle, on le touche donc toujours sur le quart HAUT GAUCHE;
    int temp_y = py;
    int temp_x = px;
    while(temp_x>0 && temp_y<data->row && (data->matrix[temp_y+1][temp_x-1]!=EMPTY || data->matrix[temp_y+1][temp_x]!=EMPTY || data->matrix[temp_y][temp_x-1] != EMPTY)){
        if(data->matrix[temp_y][temp_x-1]!=EMPTY){
            temp_x--;
        }else if(data->matrix[temp_y+1][temp_x-1]!=EMPTY){
            temp_x--;
            temp_y++;
        }
        else{
            temp_y++;
        }
    }
    Vector2 pos = {temp_x,temp_y};
    return pos;
}
BoundingBox get_bounding_box(PGMData* data, int x,int y){
    Vector2 min_y = get_min_y_position(data,x,y);
    Vector2 min_x = get_min_x_position(data,x,y);
    //Quand on a les deux bornes inférieurs et supérieures, on peut ensuite calculer les autres bornes théoriques.
    //Cela ne pose pas de soucis car si ces bornes (x+64 et y+64) ne sont pas les bonnes, cela signifie que ce n'est pas une rondelle valide
    Vector2 left_bound = {min_x.x,min_y.y};
    Vector2 right_bound = {min_x.x+65, min_y.y+65};
    BoundingBox box = {left_bound,right_bound};
    return box;
}
