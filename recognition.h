#include "pgm.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * full pixel or not
 */
#define FULL 0
#define EMPTY 255

/**
 * Struct of two ints :x and y
 * It looks like a basic point
 */
typedef struct _Vector2{
    int x;
    int y;
} Vector2;

/**
 * Struct of a vector with a link to the next to get a chained list
 * Chained list of the points of the ring
 */
typedef struct _Path{
    Vector2 pos;
    struct _Path* next;
    int val;
} Path;

/**
 * Struct containing the limite of the ring, the beginning point and the ending point
 */
typedef struct _Box{
    Vector2 begin;
    Vector2 end;
} BoundingBox;


/**
 * Simple binary thresholding 
 * @param data PGMData* your pgm data field
 * @param floor the binary floor you want
 */
void binary_floor(PGMData* data,int floor);

/**
 * Comparaison function between two elements
 * @param elem1 int first element to compare
 * @param elem2 int second element to compare
 * @return 1 if first>second, -1 if contrary
 */
int compare_two(const void * elem1, const void * elem2);

/**
 * create a path containing all the pixels stored in the model circle
 * @param data PGMData* your pgm data field
 * @return a reference to the struct created by the function
 */
Path* compute_path(PGMData* data);

/**
 * the algorithm which is checking if rings on image are correct or not
 * @param data the image on which you're testing if rings are correct or not
 * @param model the ring model as PGMData
 * @param with_reporting true if you want report in the console
 * @return a boolean corresponding to the result
 */
bool verify_image(PGMData* data,Path* model,bool with_reporting);

/**
 * this function crops all the pixels since the coordonates given as parameters 
 * which are the coordonates of the top left corner of where you're cropping, 
 * then it determinates the theoric other borders of the box following the ring model dimensions
 * @param data your PGM data field
 * @param x the beginning x
 * @param y the beginning y
 * @return the box obtained
 */
BoundingBox get_bounding_box(PGMData* data, int x,int y);

/**
 * get the min y of the given ring
 * @param data all the pixels as PGMData
 * @return the vector2 of the min y
 */
Vector2 get_min_y_position(PGMData* data,int px, int py);

/**
 * get the min x of the given ring
 * @param data all the pixels as PGMData
 * @return the vector2 of the min x
 */
Vector2 get_min_x_position(PGMData* data,int px, int py)

/**
 * initialize a path to the first black pixel encountered
 */
Path* init_path(PGMData* data, int* i, int *j);

/**
 * @param box the boudingbox you're working on
 * @param x x-coordonate of the point 
 * @param y y-coordonate of the point
 * @return the int value of the bool explaining if the given point with x andy is in the box
 */
int in(BoundingBox box, int x, int y);

/**
 * get the max y of the given ring
 * @param data all the pixels as PGMData
 * @return the int of the max x
 */
int get_max_y_position(PGMData* data, int px, int py);

/**
 * get the min y of the given ring
 * @param data all the pixels as PGMData
 * @return the int of the max x
 */
int get_max_x_position(PGMData* data, int px, int py);

/**
 * check if the following box is within the right dimension
 * @param box to check
 * @return bool corresponding to the result
 */
bool is_valid_bound(BoundingBox box);
