#include <stdio.h>
#include <stdlib.h>
#include "recognition.h"
int main(int argc, char** argv){
    if(argc != 2){
        perror("Un et un seul argument doit être passé");
        return -1;
    }
    PGMData* data = malloc(sizeof(PGMData));
    readPGM(argv[1],data);
    binary_floor(data,82);
    BoundingBox b = get_mono_bounding(data);
    PGMData* cropped = cropPGM(data,b.begin.x,b.begin.y,b.end.x,b.end.y);
    writePGM("rewritten.pgm",cropped);
    /*Path* p = compute_path(cropped);
    while(p!=NULL){
        printf("Position = %d,%d\n",p->pos.x,p->pos.y);
        p=p->next;
    }*/
}
