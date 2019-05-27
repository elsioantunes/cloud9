#!/usr/bin/python
import sys
def inputs():
    a, b = sys.stdin.readline().split()    
    a = int(a) 
    b = int(b)
    return a, b

def adj(t):
    E = [M[i] for i in F[t]]
    return E
    
def backtrack(c, t, R):
    if c:
        if c == K:
            for it in M:
                i, j, p = it
                for vira in range(2):
                    if p:
                        S[c-1] = (i, j)
                        it[2] = 0
                        backtrack(c-1, j, R)
                        it[2] = 1
                    i, j = j, i
        else:
            for it in adj(t):
                i, j, p = it
                for vira in range(2):
                    if i == t and p:
                        S[c-1] = (i, j)
                        it[2] = 0
                        backtrack(c-1, j, R)
                        it[2] = 1
                    i, j = j, i
    else:
        s = []
        for a, b in S:
            s +=  [b, a]
        R.add(tuple(s))
  
import timeit
t1 = timeit.default_timer()
    

R = set()
M = []
N, K = inputs()
print N, K

S = [0]*K
F = [[] for i in range(5*N)]

for i in range(N):
    a, b = inputs()   
    M += [[a, b]]
    F[a] += [b]
    F[b] += [a]


print M
print

f = 0
for i in F:
    print f, i
    f += 1



'''
backtrack(K, 0, R)

for i in R:
    for j in i:
        print j,
    print 

print len(R)
print timeit.default_timer() - t1

'''

