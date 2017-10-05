#!/bin/bash

cd src 
for OBJ in $2 ; 
do 
    $1 -fPIC -c $OBJ.c 
    $1 -shared -o lib$OBJ.so $OBJ.o 
done
rm -f *.o

