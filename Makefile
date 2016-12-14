CC_MPI = mpicc
CC_OMP = gcc

FLAGS = -std=c99 -O2 -g -lm
FLAGS_OMP = -fopenmp
FLAGS_MPI =

DIR_TARGET = ./bin
DIR_COMMON = ./src
SUBDIR_LAB2 = lab2

VAR1=1g
VAR2=2g

all: dirs hello_world sync cyclic sum lab_2

clean:
	rm -rf $(DIR_TARGET)/*
	rm -rf ./*.txt

dirs:
	mkdir -p $(DIR_TARGET)

hello_world:
	$(CC_OMP) $(DIR_COMMON)/hello_world.c \
	-o $(DIR_TARGET)/hello_world $(FLAGS) $(FLAGS_OMP)
sync:
	$(CC_OMP) $(DIR_COMMON)/sync.c \
	-o $(DIR_TARGET)/sync $(FLAGS) $(FLAGS_OMP)

cyclic:
	$(CC_OMP) $(DIR_COMMON)/cyclic.c \
	-o $(DIR_TARGET)/cyclic $(FLAGS) $(FLAGS_OMP)

sum:
	$(CC_OMP) $(DIR_COMMON)/sum.c \
	-o $(DIR_TARGET)/sum $(FLAGS) $(FLAGS_OMP)

lab_2: pt1 pt2

pt1:
	$(CC_OMP) $(DIR_COMMON)/$(SUBDIR_LAB2)/var_$(VAR1).c \
	-o $(DIR_TARGET)/lab2_$(VAR1) $(FLAGS) $(FLAGS_OMP)

pt2:
	$(CC_OMP) $(DIR_COMMON)/$(SUBDIR_LAB2)/var_$(VAR2).c \
	-o $(DIR_TARGET)/lab2_$(VAR2) $(FLAGS) $(FLAGS_OMP)
