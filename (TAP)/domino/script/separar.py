#!/usr/bin/python
import sys

#entrada = """22 20
entrada = """22 18
1 4
1 9
10 14
10 14
12 11
14 13
14 2
14 6
14 7
14 7
15 7
15 7
2 10
2 4
2 8
3 12
4 10
4 3
5 13
5 5
6 9
8 7""".split('\n')

entrada = [entrada[22-i] for i, it in enumerate(entrada)]

'''
entrada = """8 7
1 2
2 3
4 1
4 3
2 4
0 2
2 4
2 7""".split('\n')

entrada = [entrada[8-i] for i, it in enumerate(entrada)]
'''

def inputs():
    #a, b = sys.stdin.readline().split()    
    a, b = entrada.pop().split() 
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
    if a < b:
        a, b = b, a

    M += [[a, b, 1]]
    '''
    F[a] += [i]
    F[b] += [i]
    '''
    x, y, z = M[i]
    
    F[a] += [[x,y]]
    F[b] += [[x,y]]

    im[(a, b)] = i
    
   
print M
print
for i, it in enumerate(F):
    print i, it

for i in im:
    print i


backtrack(K, 0)

for i in R:
    for j in i:
        print j,
    print 

print len(R)
print timeit.default_timer() - t1
'''
'''

