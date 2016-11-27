CC_MPI = mpicc
CC_OMP = gcc

FLAGS = -std=c99 -O2 -g
FLAGS_OMP = -fopenmp

DIR_TARGET = ./bin
DIR_COMMON = ./src
SUBDIR_LAB2 = /lab_2

all: hello_world sync cyclic sum

clean:
	rm -rf $(DIR_TARGET)/*

hello_world:
	$(CC_OMP) $(FLAGS) $(DIR_COMMON)/hello_world.c -o $(DIR_TARGET)/\
	hello_world

sync:
	$(CC_OMP) $(FLAGS) $(DIR_COMMON)/sync.c -o $(DIR_TARGET)/sync

cyclic:
	$(CC_OMP) $(FLAGS) $(DIR_COMMON)/cyclic.c -o $(DIR_TARGET)/cyclic

sum:
	$(CC_OMP) $(FLAGS) $(DIR_COMMON)/hello_world.c -o $(DIR_TARGET)/sum
