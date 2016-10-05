#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char* argv){
    #pragma omp parallel
    {
	printf("Hello world!\n");
    }
    return 0;
}