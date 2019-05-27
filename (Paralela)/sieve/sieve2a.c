#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b)? (a): (b))


int main(int argc, char** argv)		{
    int     count;                /* local prime count */
    double  elapsed_time;         /* parallel execution time */
    int     first;                /* index of first multiple */
    int     global_count;         /* global prime count */
    int     alto;           /* highest value on this proc */
    int     i, j;
    int     id;                   /* process id number */
    int     index;                /* index of current prime */
    int     n;                    /* sieving from 2, ..., n */
    int     p;                    /* number of processes */
    int     prime;                /* current prime */
    int     segment;                 /* elements in buf string */
    int     first_value_index;
    int     prime_doubled;
    int     sqrt_n;
    int     block;
    int     low;
    int     block_alto;
    char*   buf;               /* portion of 2, ..., n */
    char*   primes;

    MPI_Init(&argc, &argv);
    MPI_Barrier(MPI_COMM_WORLD);
    elapsed_time = -MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    n = 100000000;

    
    low  = id*(n-1)/p + 2;
    alto = (id+1)*(n-1)/p + 1;
    segment = (id+1)*(n-1)/p/2 - id*(n-1)/p/2;
    
    
    //low = id*(n-1)/p + 2;
    //segment = (id+1)*(n-1)/p - low + 2;
    //alto = (id+1)*(n-1)/p  + 1;;

    //printf("id:%d, low: %d, alto:%d, segment:%d\n\n", id, low, alto, segment);
    

    // compute primes from 2 to sqrt(n);
    sqrt_n = sqrt(n);
    primes = (char*)calloc(sqrt_n + 1, 1);
    for (i = 2; i <= sqrt_n; i += 2)
        primes[i] = 1;

    for (j = 3; j <= sqrt_n; j += 2)    {
        if (primes[j] == 1) continue;
        for (i = j << 1; i <= sqrt_n; i += j)
            primes[i] = 1;
    } 
    
    buf = (char*)calloc(segment * sizeof(char), 1);
    block    = 1024 * 1024;
    block_alto = MIN(alto, low + block * 2);
    

        for (prime = 3; prime <= sqrt_n; prime++){
            if (primes[prime] == 1) continue;
            
            if (prime*prime > low){
                first = prime*prime;
            
            }else{
            	first = low;
                if (low % prime)
                    first = prime - (low % prime) + low;
           }
        
           if ((first + prime) & 1) first += prime;

           first_value_index = (first - 3) / 2 - id * (n-1) / p / 2;

           for (i = first; i <= alto; i += 2*prime)   {
               buf[first_value_index] = 1;
               first_value_index += prime;
           }
        }
        
        low += block * 2;
        block_alto = MIN(alto, block_alto + block * 2); 


    count = 0;
    for (i = 0; i < segment; i++)
        if (!buf[i])
            count++;

    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    elapsed_time += MPI_Wtime();

    if (id == 0)   {
        global_count += 1;
        printf("%d primes are less than or equal to %d\n", global_count, n);
        printf("Total elapsed time: %10.6fs\n", elapsed_time);
    } 

    MPI_Finalize();
    return 0;
}