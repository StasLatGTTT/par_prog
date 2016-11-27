CC = mpicc
FLAGS = -std=c99 -O2 -g
DIR_TARGET = ./bin
DIR_COMMON = ./src
LAB2_SUBDIR = /lab_2

all: hello_world

clean:
	rm -rf $(DIR_TARGET)/*

hello_world:
	$(CC) $(FLAGS) $(DIR_COMMON)/hello_world.c -o $(DIR_TARGET)/hello_world
