#!/usr/bin/python
# emparelhamento maximo
import sys

############################################################

def DFS(u, visto):
    for v in G[u]:
        if v in visto: continue
        visto.add(v)
        if M[v] == v or DFS(M[v], visto):
            M[v] = u
            return 1
    return 0

# emparelhamento maximo, uh!
def emp_max():
    for i, it in enumerate(X):
        if not DFS(i, set()):
            return 0
    return 1

############################################################

n = int(sys.stdin.readline())
for caso in range(n):

    y, x = [int(i) for i in sys.stdin.readline().split()]
    G = {i:[] for i in range(x)} # grafo
    X = [i for i in range(x)]      # particao pessoas
    Y = [i+x for i in range(y)]    # particao camisetas
    M = {i:i for i in range(x+y)} # emparelhamentos

    ### Liga arestas
    T = ['XXL', 'XL', 'L', 'M', 'S', 'XS']
    for i in range(x):
        for k in sys.stdin.readline().split():
            for h in range(y/6):
                G[i] += [T.index(k) + x + h*6]

    if emp_max(): print "YES"
    else: print "NO"
    



'''
problema
https://www.urionlinejudge.com.br/judge/pt/problems/view/1362

similares
https://www.urionlinejudge.com.br/judge/pt/problems/view/1330
https://www.urionlinejudge.com.br/judge/pt/problems/view/1056

'''





