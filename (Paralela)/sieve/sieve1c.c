#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include <cstdlib>
#include <stdint.h>
using namespace std;

void segmented_sieve(int64_t limit){
  int64_t factor = 6;
  int64_t sqr = (int64_t) std::sqrt(limit)*factor;
  int64_t count = (limit < 2) ? 0 : 1;
  int64_t i = 3, n = 3, s = 3, p, low, high, j, k;

  vector<char> sieve(sqr);
  vector<char> is_prime(sqr, true);
  vector<int64_t> primes;
  vector<int64_t> index;

  for (low = 0; low <= limit; low += sqr){
    fill(sieve.begin(), sieve.end(), true);

    high = min(low + sqr - 1, limit);

    for (; i * i < high; i += 2)
      if (is_prime[i])
        for (j = i * i; j < sqr/factor; j += i)
          is_prime[j] = false;
    
    for (; s * s < high; s += 2){
        if (is_prime[s]){
          primes.push_back(s);
          index.push_back(s * s - low);
        }
    }
    
    for (p = 0; p < primes.size(); p++){
        k = primes[p] * 2;
        for (j = index[p]; j < sqr; j += k)
            sieve[j] = false;
        index[p] = j - sqr;
    }

    for (; n <= high; n += 2)
        if (sieve[n - low]) 
            count++;
  }

  cout << count << " primos fodas." << endl;
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
    9 1000000000 50847534
   10 10000000000 455052511    1m51s      
   11 100000000000 4118054813     
   12 1000000000000 37607912018   
   13 10000000000000 346065536839 
*/
