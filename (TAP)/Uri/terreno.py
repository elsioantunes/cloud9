#!/usr/bin/python
import sys

###################################################################

def input(t):
    if t:
        return [int(i) for i in sys.stdin.readline().split()]
    return int(sys.stdin.readline())
 
def aumentador(u):
    for v in G[u]:
        if v in visto: continue
        visto.add(v)
        if M[v] == -1 or aumentador(M[v]):
            M[u] = v
            M[v] = u
            return 1
    return 0

###################################################################

while 1:
    K = []
    N, Q = input(1)
    if N == 0: break
    n = input(0)
    for i in range(n):
        a, b = input(1)
        K += [(a-1, b-1)]
    
    G = {}; M = {}; X = []; Y = []

    for i in range(N):
        for j in range(Q):
            key = (i, j)
            if key not in K:
                G[key] = []
                M[key] = -1
                if (i+j)%2: 
                    X += [key]
                else: 
                    Y += [key]
                
    for i in X:
        for j in Y:
            a, b = i; c, d = j
            if (abs(a-c) == 1 and b==d) or \
                (abs(b-d) == 1 and a==c): 
                G[i] += [j]
                G[j] += [i]

    emp_max = 0
    for i in G:
        if M[i] == -1:
            visto = set()
            if aumentador(i):
                emp_max += 1
    print emp_max
    
    
    
    
    
    
    
    
    
    