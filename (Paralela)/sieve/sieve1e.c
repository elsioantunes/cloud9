#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include <cstdlib>
#include <stdint.h>
using namespace std;

#define DEBUG true
//#define DEBUG false

void segmented_sieve(int64_t limit){
  const int64_t sqr = (int64_t) sqrt(limit);
  const int64_t cache = sqr*10;//32768;
  int64_t count = 0;
  int64_t i = 3, p, low, high, j, k;

  vector<char> sieve(cache);
  vector<char> is_prime(cache, true);
  vector<int64_t> primes;
  vector<int64_t> index;

  for (low = 0; low <= limit; low += cache){
    fill(sieve.begin(), sieve.end(), true);

    high = min(low + cache - 1, limit);

    for (; i * i < high; i += 2)
      if (is_prime[i]){
        for (j = i * i; j < sqr; j += i)
          is_prime[j] = false;
        
        primes.push_back(i);
        index.push_back(i * i - low);
        
      }
    
    for (p = 0; p < index.size(); p++){
        k = primes[p] * 2;
        for (j = index[p]; j < cache; j += k)
            sieve[j] = false;
        index[p] = j - cache;
    }
    

    for (p = 1; p <= high-low; p += 2){
        if (sieve[p]){
          
            //cout<< low+p << " ";
            count++;
        }
    }
    
  }

  cout << count << endl;
}


int main(int argc, char** argv){
  if (argc >= 2)
    segmented_sieve(atoll(argv[1]));
    
  else
    segmented_sieve(1000000000);

  return 0;
}

/* 
    3 1000 168  
    4 10000 1229
    5 100000 9592
    6 1000000 78498
    7 10000000 664579
    8 100000000 5761455
    9 1000000000 50847534     9.2s
   10 10000000000 455052511    1m51s !!!       
   11 100000000000 4118054813     
   12 1000000000000 37607912018   
   13 10000000000000 346065536839 
*/
