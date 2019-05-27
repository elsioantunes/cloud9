#include <mpi.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define MIN(a, b) ((a) < (b)? (a): (b))
#define print(a) printf("%ld ", a)
#define printc(a) printf(a)
#define printa(a) for(i=0;i<(a).size();i++) printf("%ld ",(a)[i]); printf("\n");
#define printai(a) for(i=1;i<(a).size();i+=2) printf("%d ",(a)[i]); printf("\n");


int main(int argc, char* argv[]){
  int myRank, nAgents;
  double elapsed_time; 
  int64_t i, n, s, h, 
          p, j, k, kk = 3, hh,
          limit = atoll(argv[1]),
          low, high, work,
          count = 0, total,
          sqr = (int64_t) sqrt(limit);

  vector<char> sieve(sqr);
  vector<char> is_prime(sqr, true);
  vector<int64_t> primes;
  vector<int64_t> index;

  
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &nAgents);
  MPI_Barrier (MPI_COMM_WORLD);
  elapsed_time = -MPI_Wtime();
  
  
  for (i = 3; i*i < sqr; i += 2)
    if (is_prime[i])
      for (j = i*i; j < sqr; j += i)
        is_prime[j] = false;

  n = 3; s = 3;
  for (low = 0; low <= limit; low += sqr){
      fill(sieve.begin(), sieve.end(), true);
      high = MIN(low + sqr, limit);

      for (; s*s <= high; s += 2){
          if (!is_prime[s]) continue;
          primes.push_back(s);
          index.push_back(s*s-low);
      }
      

      for (p = 0; p < primes.size(); p++){
          for (j = index[p]; j < sqr; j += 2*primes[p])
              sieve[j] = false;
          index[p] = j - sqr;
      }

      for (;n <= high; n += 2)
        if(sieve[n - low]) 
          count++;
  }

  MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  elapsed_time += MPI_Wtime();
  
  if(myRank == 0)
    printf("Existem %ld primos abaixo de %ld\nSieve in %10.3f\n", total+1, limit, elapsed_time);

  MPI_Finalize();
  return 0;
}