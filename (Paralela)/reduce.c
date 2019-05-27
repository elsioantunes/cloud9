/*
    many msgs:
        compara o tempo necessario para 
        mandar n mensagens de um double cada
        com o tempo de mandar uma mensagem de n doubles
        
    install:
    sudo apt-get install libmpich-dev

    compile:
    mpicc hello.c -o lol
    
    execute:
    mpirun -n 8 lol

*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
const int MAX_STRING = 100;


int main (int argc, char *argv[]){
    int i, size, myRank, soma;
    MPI_Comm comm = MPI_COMM_WORLD;
    
    soma = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
        
        
        MPI_Allreduce(&myRank, &soma, 1, MPI_INT, MPI_SUM, comm);
        
        //if(myRank == 0){
            printf("meu numero eh %d e a soma eh %d\n",myRank, soma);
            fflush(stdout);
    
            
        //}else{
            //printf("meu numero eh %d\n", myRank);
            
        //}
            



    MPI_Finalize();
    return 0;
}