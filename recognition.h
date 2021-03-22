#include "pgm.h"
#include <stdbool.h>
#define FULL 0
#define EMPTY 255
typedef struct _Vector2{
    int x;
    int y;
} Vector2;
typedef struct _Path{
    Vector2 pos;
    struct _Path* next;
    int val;
} Path;
typedef struct _Box{
    Vector2 begin;
    Vector2 end;
} BoundingBox;
void median_filter(PGMData* data);
void binary_floor(PGMData* data,int floor);
int compare_two(const void * elem1, const void * elem2);
Path* compute_path(PGMData* data);
bool verify_image(PGMData* data,Path* model,bool with_reporting);
BoundingBox get_bounding_box(PGMData* data, int x,int y);
Vector2 get_min_y_position(PGMData* data,int px, int py);
BoundingBox get_mono_bounding(PGMData* data);
Path* init_path(PGMData* data, int* i, int *j);
int in(BoundingBox box, int x, int y);
Vector2 get_max_y_position(PGMData* data, int px, int py);
Vector2 get_max_x_position(PGMData* data, int px, int py);
