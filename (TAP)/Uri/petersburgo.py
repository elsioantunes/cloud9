#!/usr/bin/python
import sys

############################################################
    
def input(t):
    if t:
        return [int(i) for i in sys.stdin.readline().split()[1:]]
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
    
############################################################


n = input(0)
for caso in range(n):
    
    X = input(1)
    Y = input(1)

    G = {}
    M = {}
    x = len(X)
    y = len(Y)
    
    for i in range(x+y): G[i] = []
    for i, it in enumerate(X):
        G[i] = []; M[i] = -1
        for j, jt in enumerate(Y):
            M[j+x] = -1
            if it == 0:
                if jt == 0:
                    G[i] += [j+x]
                    G[j+x] += [i]
            elif jt == 0: 
                G[i] += [j+x]
                G[j+x] += [i]
    
            elif jt % it == 0:
                G[i] += [j+x]
                G[j+x] += [i]
    
    visto = set()
    emp_max = 0
    
    for i, it in enumerate(X):
        if M[i] == -1:
            visto = set()
            if aumentador(i):
                emp_max += 1
    
    print "Case {0}: {1}".format(caso+1, emp_max)




'''
problema
https://www.urionlinejudge.com.br/judge/pt/problems/view/1056

forum
https://www.urionlinejudge.com.br/judge/pt/questions/view/1056/56

casos de teste
https://www.udebug.com/URI/1056

teoria
https://en.wikipedia.org/wiki/Matching_(graph_theory)
'''
