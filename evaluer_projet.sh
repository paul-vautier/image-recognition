#!/bin/bash
make clean
make
for file in ./pgm_de_test/*
do
    time ./main $file -REPORTING >> resultats.csv
done
