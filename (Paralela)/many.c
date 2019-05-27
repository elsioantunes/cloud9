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
    int i, size, myRank, n;
    double* x;
    double start, finish;
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
        
        n = 0;
        if(myRank != 0)
            n = strtol(argv[1], NULL, 10);
        
        MPI_Bcast(&n, 1, MPI_INT, 0, comm);
        
        x = malloc(n*sizeof(double));
        
        if(myRank == 0)
            for(i = 0; i < n; i ++) x[i] = i;
        else
            for(i = 0; i < n; i ++) x[i] = -1;

        
        
        MPI_Barrier(comm);
        start = MPI_Wtime();
            
            if(myRank == 0)
                for(i = 0; i < n; i ++)
                    MPI_Send(&x[i], 1, MPI_DOUBLE, 1, 0, comm);
            else
                for(i = 0; i < n; i ++)
                    MPI_Recv(&x[i], 1, MPI_DOUBLE, 0, 0, comm, &status);
        
        finish = MPI_Wtime();
        printf("** Proc %d > first comm took %e seconds\n", myRank, finish-start);
        fflush(stdout);

        
        
        
        MPI_Barrier(comm);
        start = MPI_Wtime();
            
            if(myRank == 0)
                    MPI_Send(x, n, MPI_DOUBLE, 1, 0, comm);
            else
                    MPI_Recv(x, n, MPI_DOUBLE, 0, 0, comm, &status);
                    
        finish = MPI_Wtime();
        printf("Proc %d > first comm took %e seconds\n", myRank, finish-start);
        fflush(stdout);
        
        free(x);
        
        
        

    MPI_Finalize();
    return 0;
}