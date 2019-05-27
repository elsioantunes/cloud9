/*
    install:
    sudo apt-get install libmpich-dev

    compile:
    mpicc hello.c -o lol
    
    execute:
    mpirun -n 8 lol

*/

#include <stdio.h>
#include <mpi.h>
int main (int argc, char *argv[]){
    int size, myRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    
        printf("hello! sou o processo %d de um total de %d\n", myRank, size);
        fflush(stdout);
    
    MPI_Finalize();
    return 0;
}