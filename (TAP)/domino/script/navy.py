#!/usr/bin/python
import sys
def inputs():
    a, b = sys.stdin.readline().split()    
    a = int(a) 
    b = int(b)
    return a, b
    
def backtrack(c, t):
    if c:
        for it in M:
            i, j, p = it
            for vira in range(2):
                if (i == t or c == K)  and p:
                    S[c-1] = i, j
                    it[2] = 0
                    backtrack(c-1, j)
                    it[2] = 1
                i, j = j, i
    else:
        print R[0], S
        R[0] += 1

import timeit
t1 = timeit.default_timer()
    

R = [0]
M = []
N, K = inputs()
S = [0]*K

for i in range(N):
    a, b = inputs()    
    M += [[a, b, 1]]

backtrack(K, 0)

print timeit.default_timer() - t1

