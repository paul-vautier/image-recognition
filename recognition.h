#include "pgm.h"
#define FULL 0
#define EMPTY 255
typedef struct _Vector2{
    int x;
    int y;
} Vector2;
typedef struct _Path{
    Vector2 pos;
    struct _Path* next;
} Path;
typedef struct _Box{
    Vector2 begin;
    Vector2 end;
} BoundingBox;
void median_filter(PGMData* data);
void binary_floor(PGMData* data,int floor);
int compare_two(const void * elem1, const void * elem2);
Path* compute_path(PGMData* data);
int verify_image(PGMData* data);
BoundingBox get_bounding_box(PGMData* data, int x,int y);
Vector2 get_min_y_position(PGMData* data,int px, int py);
BoundingBox get_mono_bounding(PGMData* data);
