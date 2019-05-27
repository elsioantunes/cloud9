#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

/* 
   versão do sieve 4, com otimização dos números pares.
   muito cuidado com os indexes. 
   resultam em alguns resultados verdadeiros e outros falsos.

*/

void markBlock(char* buf2, long int low, long int high, long int prime, int id){
	long int j, first = low - low%prime;
	
	if(first<low)
			first += prime;

	if(first%2 == 0)
			first += prime;

	if(first <= high){
		j = (first - low)/2;
		for(; j <= (high-low)/2; j += prime)
				buf2[j] = 1;
	}
};

long Sieve(long int n, int id, int p){
	long int i, j, k; 
	long int prime, count = 0;

	long int sqrtN = ceil((double)sqrt(n));
	long int blockSize = (n-sqrtN)/p;
	long int low, high;
	low = sqrtN + id*blockSize + 1;
	high = low + blockSize - 1;
	
	if(id == p-1) 
	   high += (n-sqrtN)%p;

	if(low%2 == 0) low++;
	//if(high%2 == 0) high--;

	char* buf1 = (char*) calloc((((sqrtN-3)/2)+1), sizeof(char));
	char* buf2 = (char*) calloc((((high-low)/2)+1), sizeof(char));
	for(i=0; i<=(sqrtN-3)/2; i++){
		if(buf1[i]) continue;
		prime = i*2 + 3;

		for(k = i + prime; k <= (sqrtN-3)/2; k += prime)
			buf1[k] = 1;

		if(id == 0)
			count++;
			
		markBlock(buf2, low, high, prime, id);
	}
	

	for(i = 0; i <= (high-low)/2; i++)
		if(!buf2[i])
			count++;
	
	free(buf1);
	free(buf2);
	return count;
}


int main(int argc, char** argv){	
	long int n = atol(argv[1]);
	int id, p;	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Barrier(MPI_COMM_WORLD);
	double principalTime, elapsedTime = -MPI_Wtime();
	long int globalSum;
	long int count;
	
	count = Sieve(n, id, p);

	elapsedTime += MPI_Wtime();
	if(id == 0) principalTime = elapsedTime;
	MPI_Reduce(&count, &globalSum, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Bcast(&principalTime, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	if(DEBUG){
		printf("rank: %d, primes: %zu, time: %lf.  Of root rank, this is : %.lf%%\n", id, count, elapsedTime, 100*elapsedTime/principalTime); 
		fflush(stdout);
	}
	if(id == 0)	{
		printf("%zu\n", globalSum + 1); 
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}


/* 
    3 1000 168
    4 10000 1229
    5 100000 9592
    6 1000000 78498
    7 10000000 664579
    8 100000000 5761455      
    9 1000000000 50847534    25.16s (5 processos)
   10 10000000000 455052511
   11 100000000000 4118054813 
   12 1000000000000 37607912018
   13 10000000000000 346065536839
*/
