#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MIN(a,b) (((a)<(b))?(a):(b))


int main(int argc, char** argv){
    int64_t n = atoll(argv[1]);
    int64_t sqr = ceil(sqrt((double)n));
    int64_t p = 3, cacheSize = 32768, high, low;
    int64_t i, j, k, count = 0;
    
    int64_t* index = (int64_t*)calloc(sqr, sizeof(int64_t));
    char* bufSqr = (char*)calloc(sqr, sizeof(char));
    
    //cacheSize = sqr + 2;
    for(low = 0; low < n; low += cacheSize){
        char* Cache = (char*)calloc(cacheSize, sizeof(char));
        
        high = MIN(low + cacheSize - 1, n);
        for(; p * p <= high; p += 2)
            if(!bufSqr[p]){
                for(j = p * p; j < sqr; j += p)
                    bufSqr[j] = 1;
                index[p] = p * p - low;
            }
            
        for(i = 3; i < sqr; i += 2)
            if(!bufSqr[i]){
                k = i * 2;
                for(j = index[i]; j < cacheSize; j += k)
                    Cache[j] = 1;
                index[i] = j - cacheSize; 
            }
    
            
        for(i = low+1; i <= high; i += 2)
            if(!Cache[i-low]){
                count++;
            }
            
    }
    printf("\n%zu\n", count);
    
    return 0;
}


/* 
    ## cloud9 ##
    
    3 1000 168
    4 10000 1229
    5 100000 9592
    6 1000000 78498   
    7 10000000 664579
    8 100000000 5761455
    9 1000000000 50847534       user 8s, real 15s
   10 10000000000 455052511     morto
   11 100000000000 4118054813 
   12 1000000000000 37607912018
   13 10000000000000 346065536839


    ## ubuntu UFABC lab ##
    
    8 100000000 5761455
    9 1000000000 50847534       user 6, real 6.3
   10 10000000000 455052511       user 1m45s, real 1m58 
   11 100000000000 4118054813       MORTO em 6m
   12 1000000000000 37607912018
   13 10000000000000 346065536839
                                                            

*/
