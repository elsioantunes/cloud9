#!/usr/bin/python 
####################################################################
import sys

def input(t):
    a = sys.stdin.readline()
    if t: return [int(i) for i in a.split()]
    return int(a)

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
'''
    Tentativa de melhorar o tempo. (deu certo!)
    Mas o codigo ja passou no URI sem essas tres proximas funcoes
    
    A manha eh separar a lista em duas: uma com problema e outra sem.
    considero problema aninhamentos de valores iguais encavalados.
    Quando isso acontece, precisamos de uma funcao recursiva pra decidir
    qual encavalada vamos desmontar pra ganhar o maximo de pontos com o que sobra. 
    Isso consome muito ciclo. Por outro lado, se nao tiver nada envavalado
    so conta os pontos e me da meu copo...
'''
def solve_simples(b2):
    cont = {}
    for i in b2:
        if i not in cont: cont[i] = 0
        cont[i] += 1
    ret = 0
    for i in cont:
        ret += cont[i] * cont[i]
    return ret

def separa(arr):
    rep = {}
    arr += [0]
    B1 = []; B2 = []
    for i in range(len(arr)-1):
        b = arr[i]
        if b != arr[i+1]: 
            if b not in rep: rep[b] = -1
            rep[b] +=1

    for i in range(len(arr)-1):
        b = arr[i]
        if rep[b]: B1 += [b]
        else: B2 += [b]

    return B1, B2

def separa_rec(b):
    B1 = b
    B2 = b
    B3 = []
    while B1 and B2:
        B1, B2 = separa(B1)
        B3 += B2

    return B1, B3

####################################################################

for i in range(input(0)):
    nblocks = input(0)
    blocks = input(1)
    buf = {}
    
    B1, B2 = separa_rec(blocks)
    blocks = B1

    r1 = solve(0, len(blocks)-1, 1)
    r2 = solve_simples(B2)
    
    print "Case {0}: {1}".format(i+1, r1+r2)
    
    