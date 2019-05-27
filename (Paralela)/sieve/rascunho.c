#define MIN(a, b) ((a) < (b)? (a): (b))



#define BLOCK_LOW(id, p, n) ((id) * (n) / (p) / 2)

#define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, p, n) - 1)

#define BLOCK_SIZE(id, p, n) (BLOCK_LOW((id) + 1, p, n) - BLOCK_LOW((id), p, n))

#define BLOCK_OWNER(index, p, n) (((p) * ((index) + 1) - 1) / (n))

#define BLOCK_VALUE_TO_INDEX(val, id, p, n)  (val - 3) / 2 - BLOCK_LOW(id, p, n - 1)


    sqrt_n = sqrt(n);
    primes = (char*)calloc(sqrt_n + 1, 1);
    for (i = 2; i <= sqrt_n; i += 2)
        primes[i] = 1;

    for (prime = 3; prime <= sqrt_n; prime += 2)    {
        if (primes[prime] == 1) continue;
        for (i = prime << 1; i <= sqrt_n; i += prime)
            primes[i] = 1;
    } 
    
    /* 
    3 1000 168
    4 10000 1229
    5 100000 9592
    6 1000000 78498
    7 10000000 664579
    8 100000000 5761455
    9 1000000000 50847534
   10 10000000000 455052511 *
   11 100000000000 4118054813 
   12 1000000000000 37607912018
   13 10000000000000 346065536839
*/

0, 9
0, 17
0, 23
0, 29
0, 35
0, 41
0, 46
0, 52
0, 58
0, 62
0, 67
0, 72
0, 78
0, 83
0, 89
0, 93
0, 98
0, 101
0, 106
0, 113
0, 117
0, 122
0, 126
0, 131
0, 136
0, 138
0, 144
0, 149
0, 153
0, 157
0, 161
0, 166
0, 167