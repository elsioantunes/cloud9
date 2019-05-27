/*
    Sieve of Eratosthenes:
        O classico crivo de primos

    install:
    sudo apt-get install libmpich-dev

    compile:
    mpicc sieve.c -o lol
    
    execute:
    mpirun -n 8 lol

*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main (int argc, char *argv[]){
    int i, j, size, myRank;
    MPI_Comm comm = MPI_COMM_WORLD;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

        if(myRank == 0){
        }
        
        MPI_Bcast(&m, 1, MPI_INT, 0, comm);
        MPI_Bcast(&n, 1, MPI_INT, 0, comm);
        
        localM = m/size;
        localN = n/size;
        
        // alocate arrays
        local_A = malloc(localM*n*sizeof(double));
        local_x = malloc(localN*sizeof(double));
        local_y = malloc(localM*sizeof(double));

        // read matrix
        if(myRank == 0){
            A = malloc(m*n*sizeof(double));
            printf("entre com a matriz\n");
            for(i=0; i<m; i++)
                for(j=0; j<n; j++)
                    scanf("%lf", &A[i*n+j]);
        }
        MPI_Scatter(A, localM*n, MPI_DOUBLE, local_A, localM*n, MPI_DOUBLE, 0, comm);
        free(A);
        

        // read vector
        if(myRank == 0){
            x = malloc(n*sizeof(double));
            printf("entre com o vetor\n");
            for(i=0; i<n; i++)
                scanf("%lf", &x[i]);
        }
        MPI_Scatter(x, localN, MPI_DOUBLE, local_x, localN, MPI_DOUBLE, 0, comm);
        free(x);
        
        

        /*
        // mult matriz
        x = malloc(n*sizeof(double));
        MPI_Allgather(local_x, localN, MPI_DOUBLE, x, localN, MPI_DOUBLE, comm);
        
        for (local_i=0; local_i< localM; local_i++){
            local_y[local_i] = 0.0;
            for(j=0; j<n; j++)
                local_y[local_i] += local_A[local_i*n+j]*x[j];
        }
        free(x);
        */
        
        for(i=0; i<localM; i++){
            local_y[i] = 0.0;
            for(j=0; j<m; j++)
                local_y[i] += local_A[j]*x[j];
        }
        
        printf("meu rank eh %d\n", myRank);
        for(j=0; j<n; j++)
            printf("A[j]: %f, x[j]: %f\n",local_A[j], x[j]);

        
        
        
        
        // print matrix
        if(myRank == 0){
            printf("imprimindo o vetor\n");
            y = malloc(m*sizeof(double));
            MPI_Gather(local_y, localM, MPI_DOUBLE, y, localM, MPI_DOUBLE, 0, comm);
            for(i=0; i<m; i++)
                printf("%f ", y[i]);
            printf("\n");
            free(y);
        
            
        }else{
            
            MPI_Gather(local_y, localM, MPI_DOUBLE, y, localM, MPI_DOUBLE, 0, comm);
            
        }
        
        

        free(local_A);
        free(local_x);
        free(local_y);
        

        

    MPI_Finalize();
    return 0;
}