#!/usr/bin/python
import sys
def inputs():
    a, b = sys.stdin.readline().split()    
    return int(a), int(b)
########################################################################


def backtrack(count, last):
    if count:

        if count == lenFita:
            for peca in monte:
                a, b, noUsed = peca
                if  noUsed:
                    for vira in range(2):
                        fita[count-1] = b, a
                        peca[2] = 0
                        backtrack(count-1, b)
                        peca[2] = 1
                        if a == b: break
                        a, b = b, a
                    
        else:        
            for peca in monte:
                a, b, noUsed = peca
                if a == last or b == last: 
                    if noUsed:
                        for vira in range(2):
                            if (a == last):
                                fita[count-1] = b, a
                                peca[2] = 0
                                backtrack(count-1, b)
                                peca[2] = 1
                            if a == b: break
                            a, b = b, a
                
    
    else: 
        t = tuple(fita[:])
        if t not in Fitas:
            Fitas.add(t)


import time
t1 = time.time()
uniq = set()
Fitas = set()
monte = []
lenMonte, lenFita = inputs()
fita = [0]*lenFita

for i in range(lenMonte):
    a, b = inputs()
    monte += [[a, b, 1]]

backtrack(lenFita, 0)

for fita in Fitas:
    for peca in fita: 
        print peca[0], peca[1], 
    print

print time.time() - t1