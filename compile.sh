#!/bin/bash
gcc ./src/$1.c -o ./bin/$1 -std=c99 -g -fopenmp
