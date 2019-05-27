#!/usr/bin/python
import sys

entrada = """22 20
0 7
5 5
15 7
4 10
10 0
3 12
10 0
5 13
8 7
0 6
4 3
12 11
6 9
1 9
0 13
1 4
0 2
2 4
2 10
0 7
15 7
2 8""".split('\n')

entrada = [entrada[22-i] for i, it in enumerate(entrada)]

def inputs():
    a, b = sys.stdin.readline().split()    
    #a, b = entrada.pop().split() 
    a = int(a) 
    b = int(b)
    return a, b
    
def backtrack(c, t):
    if c:
        if c == K:        
            for f in im:
                it = M[im[f]]
                i, j, p = it
                for vira in range(2):
                    if p:
                        S[c-1] = i, j
                        it[2] = 0
                        backtrack(c-1, j)
                        it[2] = 1
                    i, j = j, i
        else:
            for it in M:
                #it = M[f]
                i, j, p = it
                for vira in range(2):
                    if i == t  and p:
                        S[c-1] = i, j
                        it[2] = 0
                        backtrack(c-1, j)
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
im = {}
N, K = inputs()


S = [0]*K
F = [[] for i in range(N*2)]

for i in range(N):
    a, b = inputs()    
    M += [[a, b, 1]]
    '''
    F[a] += [i]
    F[b] += [i]
    '''
    x, y, z = M[i]
    
    F[a] += [[x,y]]
    F[b] += [[x,y]]

    if a < b:
        a, b = b, a
    im[(a, b)] = i
    
   
   
print M
print
for i, it in enumerate(F):
    print i, it


backtrack(K, 0)

for i in R:
    for j in i:
        print j,
    print 

print len(R)
print timeit.default_timer() - t1
'''
'''

