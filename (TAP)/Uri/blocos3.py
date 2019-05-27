#!/usr/bin/python 
####################################################################
import sys

def input(t):
    a = sys.stdin.readline()
    if t: return a.split()
    return int(a)

####################################################################

'''
    Tentativa de melhorar o tempo. (deu certo!)
    Mas o codigo ja passou no URI sem essas tres primeiras funcoes
    
    A manha eh separar a lista em duas: uma com problema e outra sem.
    considero problema aninhamentos de valores iguais encavalados.
    Quando isso acontece, precisamos de uma funcao recursiva pra decidir
    qual encavalada vamos desmontar pra ganhar o maximo de pontos com o que sobra. 
    Isso consome muito ciclo. Por outro lado, se nao tiver nada envavalado
    so conta os pontos e me da meu copo...
'''

def separa():
    cont = {}
    for i in C:
        if i[1] not in cont:
            cont[i[1]] = -1
        cont[i[1]] += 1

    b1 = []; b2 = []
    for i in blocks:
        if i and cont[i] or i == 0: 
            b1 += [i]
        else: b2 += [i]
    
    return b1, solve_simples(b2)
    
def entrada():
    _ = input(0)
    B = input(1) + [0]
    b = []
    C = []
    for i in range(len(B)-1):
        b += [B[i]]
        if B[i] != B[i+1] : 
            C += [(len(b), b[0])]
            b = []
    return B, C

def solve_simples(b2):
    cont = {}
    for i in b2:
        if i not in cont: cont[i] = 0
        cont[i] += 1
    ret = 0
    for i in cont:
        ret += cont[i] * cont[i]
    return ret

####################################################################

def solve(l, r, n):
    if l > r: return 0
    if (l, r, n) in buf: return buf[(l, r, n)]
    m = n*n
    M = m + solve(l+1, r, 1)
    for i in range(l+1, r+1):
        if blocks[i] == blocks[l]:
            M = max(M, solve(l+1, i-1, 1) + solve(i, r, n+1)) 
    if (l, r, n) not in buf: buf[(l, r, n)] = M
    return M

####################################################################

for caso in range(1, input(0)+1):
    buf = {}
    blocks, C = entrada()
    b1, r1 = separa()

    blocks = b1
    r2 = solve(0, len(blocks)-2, 1)
    #print b1, r1

    print "Case {0}: {1}".format(caso, r1+r2)



