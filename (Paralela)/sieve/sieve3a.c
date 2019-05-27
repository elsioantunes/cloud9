#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MIN(a, b) ((a)<(b)?(a):(b))
#define ID_ROOT 0
#define FALSE 0
#define TRUE 1

unsigned int crivo_paralelo_dados (unsigned int n , int id , int p ){
    unsigned int count; 
    unsigned int first;
    unsigned int high_value; 
    unsigned int i;
    unsigned int index; 
    unsigned int low_value; 
    char *marked; 
    unsigned int proc0_size; 
    unsigned int prime; 
    unsigned int size; 
    
    low_value = 2 + id *(n-1)/p;
    high_value = 1 + (id+1)*(n-1)/p;
    size = high_value - low_value + 1;
    
    marked = (char*) malloc(size * sizeof(char));
    
    for(i=0; i<size; i++)
    	marked[i] = FALSE;
    	
    if(id == ID_ROOT)
    	index = 0;
    	
    prime = 2;
    
    do{
	    if (prime*prime > low_value){
	    	first = prime*prime - low_value;
	    
	    }else{
    		if ((low_value % prime ) == 0 )
    		    first = 0;
    		else
    		    first = prime - (low_value % prime);
	    }
	    
	    for(i = first; i < size; i += prime) 
	    	marked [i] = TRUE;
	    	
	    if (id == ID_ROOT){
	    	while (marked[++index] == TRUE);
		    prime = index + 2;
	    }
	    
	    if (p>1)
	    	MPI_Bcast(&prime, 1, MPI_INT, ID_ROOT, MPI_COMM_WORLD);
	    	
    } while (prime * prime <= n);
    
    count = 0;
    for(i=0; i<size; i++)
    	if(marked[i] == FALSE)
    		count++;
    
    free(marked);
    return count;
}
int main (int argc, char* argv[]){
    unsigned int count;
    double elapsed_time; 
    unsigned int global_count;
    int id;
    unsigned int n;
    int p; 
    
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &p);
    
    MPI_Barrier (MPI_COMM_WORLD);
    elapsed_time = -MPI_Wtime();
    
    n = (unsigned int) atoll(argv[1]);
    count = crivo_paralelo_dados(n, id, p);
    
    if (p > 1)
    	MPI_Reduce(&count, &global_count, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
    else
    	global_count = count;

    elapsed_time += MPI_Wtime();
    
    if (id == 0){    
	    printf ("There are %u primes less than or equal to %u\n", global_count, n);
	    printf ("SIEVE (%d) %10.6f\n", p, elapsed_time);
	    printf("%d\t%lf\n", p, elapsed_time);
    }
    
    MPI_Finalize();
    return 0;
}