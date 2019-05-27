#!/usr/bin/python
import sys
import random
print random.random()

'''

PEOES = 3
CASAS = 5
'''
PEOES = 5
CASAS = 8

def printcol(n):
   for i in range(CASAS):
      if col[n][0] == i: print "0 ",
      elif col[n][1] == i: print "X ",
      else: print ". ",
   print

def printbin(n, dig):
    str = ""
    for i in range(dig):
        s = n % 2
        n = (n-s)/2
        if s: str = "O " + str
        else: str = ". " + str
    return str

def bitCount(n):
    b = 0
    while (n):
        b += n & 1
        n >>= 1
    return b

def bitPos(n):
    r = []
    c = 0
    while (n):
        if n & 1: r += [c]
        c += 1
        n >>= 1
    return r

def C(n, k):
	if k > n: return  0
	if k > n / 2: k = n - k
	res = 1
	for i in range(k):
		res *= n - i 
		res /= i + 1 
	return res

def mersenne(a):
    return (1 << a) - 1

def gosper(a):
    c = a & -a
    r = a + c
    return (((r ^ a) >> 2 )/c) | r


def combina(ID):
    '''
    Essa funcao busca posicionar separadores no vetor (usando gosper())
    de modo a obter todas as combinacoes de sequencias nao repetidas
    
    C(4, 0) = 1   a a a a a
    C(4, 1) = 4   a|b b b b  a a|b b b  a a a|b b  a a a a|b
    C(4, 2) = 6   a|b|c c c  a|b b|c c  a|b b b|c  a a|b|c c  a a|b b|c   a a a|b|c 
    C(4, 3) = 4   a|b|c|d d  a|b|c c|d  a|b b|c|d  a a|b|c|d
    C(4, 4) = 1   a|b|c|d|e  
   
    '''    
    seq = bitPos(ID)
    vlen = len(seq)
    if vlen == 1:
        return [[seq[0] for i in range(PEOES)]]
    m = mersenne(vlen-1)
    res = []
    for i in range(C(PEOES-1, vlen-1)):
        r = [seq[0]]
        c = 0
        n = m
        for j in range(PEOES-1):
            if n & 1: c += 1
            n >>= 1
            r += [seq[c]]
        m = gosper(m)
        res += [r]
    return res


def grafcol(player, id):
    O = col[id][0]
    X = col[id][1]
    M = []
    if player == 0:
        if O + 1 == X and X != CASAS-1:
            M += [idcol[O+2, X]]
        else: 
            lim = X if (O < X) else CASAS
            for i in range(O + 1, lim):
                M += [idcol[i, X]]
    else:
        if O + 1 == X and O != 0:
            M += [idcol[O, X-2]]
        else: 
            for i in range(O+1 if (O < X) else 0, X):
                M += [idcol[O, i]]
    return M
    
                

def terminal(ids):
    t1 = 1
    for i in ids:
        if col[i][1] != 0:
            t1 = 0
    t0 = 1
    for i in ids:
        if col[i][0] != CASAS-1:
            t0 = 0
        
    return t0 or t1

def graftab(player, ids):
    M = set()
    if terminal(ids): 
        return M 
    k = [0,0,0]
    for i in range(PEOES):
        k[0], k[1], k[2] = ids
        for j in grafcol(player, k[i]):
            k[i] = j
            M.add((k[0], k[1], k[2]))
    if len(M) == 0:
        M.add(tuple(ids))
    
    res = set() 
    for i in M:
        v = list(i)
        v.sort()
        res.add(tuple(v))
    return res

#############################################################

comb = C(CASAS,2)*2   # 20, 56 
col = [(i, j) for i in range(CASAS) for j in range(CASAS) if i != j]
idcol = {it:i for i, it in enumerate(col)}




def maketab():
    res = []
    for i in range(PEOES): 
        ID = mersenne(i+1)
        for j in range(C(comb, i+1)):
            res += [ID]
            ID = gosper(ID)
    return res


'''
tab = maketab()
print len(tab)

res = [combina(i) for i in tab]
print len(res)
'''



'''    


k = 0
for i in range(550731776):
    k = 1
print k
'''




'''
    1   1   1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388608 16777216 33554432 67108864 134217728 268435456 536870912
    2   4   3 5 6 9 10 12 17 18 20 24 33 34 36 40 48 65 66 68 72 80 96 129 130 132 136 144 160 192 257 258
    3   6   7 11 13 14 19 21 22 25 26 28 35 37 38 41 42 44 49 50 52 56 67 69 70 73 74 76 81 82 84 88
    4   4   15 23 27 29 30 39 43 45 46 51 53 54 57 58 60 71 75 77 78 83 85 86 89 90 92 99 101 102 105 106
    5   1   31 47 55 59 61 62 79 87 91 93 94 103 107 109 110 115 117 118 121 122 124 143 151 155 157 158 167 171 173 174

'''



        

'''


conf = [1,6,2]
for i in conf:
    printcol(i)
print
print "-------------"
print

for i in graftab(1, conf):
    for j in i:
        printcol(j)
    print



'''


'''
 C(5, 2) * 2 = 20
 C(8, 2) * 2 = 56

 C(20, 1) * C(2, 0) = 20      * 1   = 20     (a, a, a)  
 C(20, 2) * C(2, 1) = 190     * 2   = 390    (a, a, b) (a, b, b)  
 C(20, 3) * C(2, 2) = 1140    * 1   = 1140   (a, b, c)
                    + 1350          + 1540 
                      
 C(56, 1) * C(4, 0) = 56      * 1  = 56        (a, a, a, a, a)   
 C(56, 2) * C(4, 1) = 1540    * 4  = 6160      (a, b, b, b, b) (a, a, b, b, b) (a, a, a, b, b) (a, a, a, a, b)
 C(56, 3) * C(4, 2) = 27720   * 6  = 166320    (a, a, a, b, c) (a, b, b, b, c) (a, b, c, c, c) (a, a, b, b, c) (a, a, b, c, c) (a, b, b, c, c) 
 C(56, 4) * C(4, 3) = 367290  * 4  = 1469160   (a, a, b, c, d) (a, b, b, c, d) (a, b, c, c, d) (a, b, c, d, d) 
 C(56, 5) * C(4, 4) = 3819816 * 1  = 3819816   (a, b, c, d, e)
                    + 4216422      + 5461512

0   0 X . . .
1   0 . X . .
2   0 . . X .
3   0 . . . X
4   X 0 . . .
5   . 0 X . .
6   . 0 . X .
7   . 0 . . X
8   X . 0 . .
9   . X 0 . .
10  . . 0 X .
11  . . 0 . X
12  X . . 0 .
13  . X . 0 .
14  . . X 0 .
15  . . . 0 X
16  X . . . 0
17  . X . . 0
18  . . X . 0
19  . . . X 0


'''