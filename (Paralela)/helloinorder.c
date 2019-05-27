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
#include <string.h>
const int MAX_STRING = 100;

int main (int argc, char *argv[]){
    int i, size, myRank;
    char str[MAX_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
        
        if(myRank != 0){
            sprintf(str, "Olah, eu sou o processo %d de %d", myRank, size);
            MPI_Send(str, strlen(str)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            
        }else{
            printf("Olah, eu sou o CHEFE\n");
            for(i=1; i<size; i++){
                MPI_Recv(str, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("%s\n", str);
            }
        }

    MPI_Finalize();
    return 0;
}