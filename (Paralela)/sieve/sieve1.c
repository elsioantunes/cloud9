/// @file     segmented_sieve.cpp
/// @author   Kim Walisch, <kim.walisch@gmail.com> 
/// @brief    This is a simple implementation of the segmented sieve of
///           Eratosthenes with a few optimizations. It generates the
///           primes below 10^9 in 0.8 seconds (single-threaded) on an
///           Intel Core i7-6700 3.4 GHz CPU.
/// @license  Public domain.

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>
using namespace std;

/// Set your CPU's L1 data cache size (in bytes) here
const int64_t L1D_CACHE_SIZE = 32768;

/// Generate primes using the segmented sieve of Eratosthenes.
/// This algorithm uses O(n log log n) operations and O(SQR(n)) space.
/// @param limit  Sieve primes <= limit.
///
void segmented_sieve(int64_t limit){
  int64_t SQR = (int64_t) sqrt(limit);
  int64_t segment_size = max(SQR, L1D_CACHE_SIZE);
  int64_t count = (limit < 2) ? 0 : 1;

  // we sieve primes >= 3
  int64_t i = 3;
  int64_t n = 3;
  int64_t s = 3;

  vector<char> sieve(segment_size);
  vector<char> is_prime(SQR + 1, true);
  vector<int64_t> primes;
  vector<int64_t> multiples;

  for (int64_t low = 0; low <= limit; low += segment_size) {
    fill(sieve.begin(), sieve.end(), true);

    // current segment = [low, high]
    int64_t high = low + segment_size - 1;
    high = min(high, limit);

    // generate sieving primes using simple sieve of Eratosthenes
    for (; i * i <= high; i += 2)
      if (is_prime[i])
        for (int64_t j = i * i; j <= SQR; j += i)
          is_prime[j] = false;

    // initialize sieving primes for segmented sieve
    for (; s * s <= high; s += 2){
      if (is_prime[s]){
           primes.push_back(s);
        multiples.push_back(s * s - low);
      }
    }

    // sieve the current segment
    for (size_t i = 0; i < primes.size(); i++){
      int64_t j = multiples[i], k = primes[i] * 2;
      
      for (; j < segment_size; j += k)
        sieve[j] = false;
      multiples[i] = j - segment_size;
    }

    for (; n <= high; n += 2)
      if (sieve[n - low]) // n is a prime
        count++;
  }

  cout << count << " primes found." << endl;
}

/// Usage: ./segmented_sieve n
/// @param n  Sieve the primes up to n.
///
int main(int argc, char** argv){
  if (argc >= 2)
    segmented_sieve(atoll(argv[1]));
  else
    segmented_sieve(1000000000);

  return 0;
}