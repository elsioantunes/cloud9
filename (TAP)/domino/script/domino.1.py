#!/usr/bin/python
import sys
import timeit
t1 = timeit.default_timer()
debug = 1

def inputs():
    a, b = sys.stdin.readline().split()    
    a = int(a) 
    b = int(b)
    return a, b

#########################################################

def printresults():
    for fita in results:
        for peca in fita:
            print peca,
        print 

def makelist():
    for i in range(N):
        p = inputs()    
        if not p in Pecas:
            Pecas[p] = 1
        else:
            Pecas[p] += 1

def mergeresult(fita):
    s = []
    for a, b in fita:
        s += [a, b]
    results.add(tuple(s))

#########################################################

def backtrack(n, last):
    if n < K:
        if n == 0:
            for p in Pecas:
                a, b = p
                for vira in range(2):
                    if Pecas[p]:
                        Fita[n] = a, b
                        Pecas[p] -= 1
                        backtrack(n + 1, b)
                        Pecas[p] += 1
                    a, b = b, a
        else:
            for p in Pecas:
                a, b = p
                for vira in range(2):
                    if a == last and Pecas[p]:
                        Fita[n] = a, b
                        Pecas[p] -= 1
                        backtrack(n + 1, b)
                        Pecas[p] += 1
                    a, b = b, a
    else:
        mergeresult(Fita)

#########################################################

N, K = inputs()
results = set()
Pecas = {}
Fita = [0]*K

makelist()
backtrack(0, 0)
printresults()


if debug:
    print len(results)
    print timeit.default_timer() - t1

