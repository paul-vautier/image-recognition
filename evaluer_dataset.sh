#!/bin/bash
make clean
make
for dir in ./dataset/*
do
    for file in $dir/*
    do
        time ./main $file -REPORTING >> dataset.csv
    done
done
