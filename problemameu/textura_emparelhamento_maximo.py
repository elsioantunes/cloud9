#!/usr/bin/python
import sys

###################################################################

def input(t):
    if t:
        return [int(i) for i in sys.stdin.readline().split()]
    return int(sys.stdin.readline())
 
def DFS(u, visto):
    for v in G[u]:
        if v in visto: continue
        visto.add(v)
        if M[v] == -1 or DFS(M[v], visto):
            M[u] = v
            M[v] = u
            return 1
    return 0

def emp_max():
    return len([
        1 
        for i, it in enumerate(X) 
            if M[i] == -1 and DFS(i, set())
        ]
    )

###################################################################
while 1:
    K = []
    N, Q = input(1)
    if N == 0: break
    n = input(0)
    for i in range(n):
        a, b = input(1)
        K += [(a-1, b-1)]
    
    G = {}; M = []; X = []; Y = []

    c = 0
    for i in range(N):
        for j in range(Q):
            G[c] = []
            M += [-1]
            if (i, j) not in K:
                if (i+j)%2: X += [c]
                else: Y += [c]
            c += 1
    
    for i, it in enumerate(X):
        for j in [it+1, it-1, it+N, it-N]:
            if j in Y:
                G[i] += [Y.index(j)+N]
                
                
    print X
    print Y
    
    for i in G:
        print i, G[i]
        
        '''
        for j in G[i]:
            print Y[j],
        print 
        '''
    

    print emp_max()

