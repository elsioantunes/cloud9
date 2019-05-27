#!/usr/bin/python
import sys
def inputs():
    a, b = sys.stdin.readline().split()    
    return int(a), int(b)

########################################################################


class Peca(object):
    def __init__(self, a, b):
        self.adj = []
        self.a = a
        self.b = b
        self.used = 0


def backtrack(count, last):
    if count:
        for peca in monte:
            a, b, noUsed = peca
            
            for vira in range(2):
                if (a == last or count == lenFita) and noUsed:
                    fita[count-1] = b, a
                    peca[2] = 0
                    backtrack(count-1, b)
                    peca[2] = 1
                a, b = b, a
    
    else: Fitas.append(fita[:])

Fitas = []
monte = []
lenMonte, lenFita = inputs()
fita = [0]*lenFita

for i in range(lenMonte):
    a, b = inputs()
    monte += [[a, b, 1]]
    


import time
t1 = time.time()
backtrack(lenFita, 0)



S = {tuple(fita) for fita in Fitas}
'''
for fita in S:
    for peca in fita: print peca[0], peca[1], 
    print
'''

print 
print len(S)
print time.time() - t1
