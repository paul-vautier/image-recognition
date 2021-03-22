#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "recognition.h"
int main(int argc, char** argv){
    clock_t begin = clock();
    if(argc != 2 && argc != 3){
        perror("Un et un seul argument doit être passé");
        return -1;
    }
    bool report = false;
    if(argc == 3 && strcmp(argv[2],"-REPORTING")){
        perror(argv[2]);
        perror("Argument incorrect");
        return -1;
    }else if(argc == 3 && !strcmp(argv[2],"-REPORTING")){
        report = true;
    }

    PGMData* model = malloc(sizeof(PGMData));
    readPGM("./cropped.pgm",model);
    Path* path = compute_path(model);

    PGMData* data = malloc(sizeof(PGMData));
    readPGM(argv[1],data);
    binary_floor(data,80);
    bool res = verify_image(data,path,report);

    clock_t end = clock();
    double spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Fichier : %s, Résultat : %s, Temps exécution : %f\n\n",argv[1], res == false ? "Refusé" : "Accepté", spent);
    return 0;
}
