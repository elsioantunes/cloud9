#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

// https://github.com/rbsteinm/MPI-Sieve-Of-Eratosthenes/blob/master/erato_parallel.cpp

int main(int argc, char* argv[]) {

    int p; // number of processes
    int rank; // rank of the current process
    int DEBUG = 1;
    unsigned long n;
    unsigned long low;
    unsigned long size;
    unsigned long i;
    unsigned long k;
    unsigned long first;
    unsigned long next_k;
    unsigned int local_sum;
    unsigned int global_sum;

    MPI_Init(&argc, &argv); // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    double time = MPI_Wtime();

    n = (unsigned int) atoll(argv[1]);

    low = rank*(n-2)/p + 2;
    size = (rank+1)*(n-2)/p - low + 2;

    bool *array = new bool[size];
    for(i = 0; i < size; i++){
        array[i] = true; // first every element is marked as prime
    }

    k = 2;

    while(k*k <= n){
        
        first = 0;
        if(low % k) 
            first = k - low % k;
            
        for(i = first; i < size; i += k)
            array[i] = false;

        if(rank == 0){
            array[k-2] = true;
            next_k = k+1;
            while(!array[next_k - 2]) 
                next_k = next_k + 1;
            k = next_k;
        }
        
        MPI_Bcast (&k,  1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    
    local_sum = 0;
    for(i = 0; i < size; i++)
        if (array[i]) local_sum++;

    MPI_Reduce (&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        time = MPI_Wtime() - time;
        printf("There are %d prime numbers under %lu. \n", global_sum, n);
        printf("The algorithm took %f seconds to execute \n\n", time);
    }

    delete(array);
    MPI_Finalize();
}