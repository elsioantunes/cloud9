#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN(a, b) ((a)<(b)?(a):(b))

int64_t crivo (int64_t n , int id , int p){
    MPI_Status status;
    int64_t prime, prime2, low, first, rest, segment, count, i, j, index; 
    char *buf; 

    low = id*(n-1)/p + 2;
    segment = (id+1)*(n-1)/p - low + 2;
    buf = (char*) calloc(segment,  sizeof(char));
    //printf("id:%d, low: %d, segment:%d\n\n", id, low, segment);
    if(id == 0) 
        index = 0;
    	
    prime = 2;
    prime2 = 4; 

    while (prime2 <= n){
        first = 0;
        rest = low % prime;
        if (rest)
            first = prime - rest;
	    
	    if (prime2 > low)
	    	first = prime2 - low;
	    
	    for(i = first; i < segment; i += prime) 
	    	buf[i] = true;
	    	
	    if (id == 0){
	    	do{
	    	    index++;
	    	} while(buf[index]== true);
	    	
	    	prime = index + 2;
	    }
	    
	    if (p > 1) {
	       if (id > 0) 
	            MPI_Recv (&prime, 1, MPI_INT, id-1, 0, MPI_COMM_WORLD, &status);
	            
	       if (id < (p-1)) 
	           MPI_Send (&prime, 1, MPI_INT, id+1, 0, MPI_COMM_WORLD);
	    }
    	prime2 = prime*prime;
    };
    
    count = 0;
    for(i=0; i<segment; i++)
    	if(!buf[i])
    		count++;
    
    free(buf);
    return count;
}

int main (int argc, char* argv[]){
    int64_t count;
    double elapsed_time; 
    int64_t global_count;
    int id;
    int64_t n;
    int p; 
    
    
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &p);
    
    MPI_Barrier (MPI_COMM_WORLD);
    elapsed_time = -MPI_Wtime();
    
    n = (unsigned int) atoll(argv[1]);
    count = crivo(n, id, p);
    
    MPI_Reduce(&count, &global_count, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
 
    elapsed_time += MPI_Wtime();
    
    if (id == 0){    
	    printf ("There are %ld primes less than or equal to %ld\n", global_count, n);
	    printf ("SIEVE (%d) %10.6f\n", p, elapsed_time);
   }
    
   MPI_Finalize();
   return 0;
}