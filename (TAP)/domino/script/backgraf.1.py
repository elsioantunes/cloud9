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
            for vira in range(2):
                if (peca.a == last or count == lenFita) and not peca.used:
                    fita[count-1] = peca.a, peca.b
                    peca.used = 1
                    backtrack(count-1, peca.b)
                    peca.used = 0
                peca.a, peca.b = peca.b, peca.a
    

    else: 
        '''
        t = tuple(fita)
        if t not in uniq:
            for p in fita:
                print p[0], p[1], 
            print
        uniq.add(t)
        '''
        U = 0

U = []
uniq = set()
Fitas = []
monte = []
lenMonte, lenFita = inputs()
fita = [0]*lenFita

for i in range(lenMonte):
    a, b = inputs()
    p = Peca(a, b)
    monte.append(p)



import time
t1 = time.time()
backtrack(lenFita, 0)


'''
for i in monte:
    print i.a, i.b, " ",
print
'''

print len(U)
print time.time() - t1
