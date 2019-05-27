#############################################################

def printTab(n):
    print n
    for i in confTab[n]:
        printConfCol(i)
    print

#############################################################

def printConfCol(n):
   for i in range(5):
      if confCol[n][0] == i: print "0",
      elif confCol[n][1] == i: print "X",
      else: print ".",
   print

#############################################################

def terminal(n):
    k = confTab[n]
    p0 = 0
    p1 = 0
    if confCol[k[0]][0] == 4 and confCol[k[1]][0] == 4 and confCol[k[2]][0] == 4: p0 = 1
    if confCol[k[0]][1] == 0 and confCol[k[1]][1] == 0 and confCol[k[2]][1] == 0: p1 = 1
    return p1*2+p0

#############################################################

def grafCol(player, n):
    if player == 1:
        return [[], [0], [0,1], [0,1,2], [], [4], [5], [5,6], 
        [], [8], [9], [10], [], [12], [12,13], [14], [], [16],
        [16,17], [16,17,18]][n]
    return [
        [9], [5], [6,10], [7,11,15], [8,12,16], [14], 
        [10], [11,15], [12,16], [13,17], [19], [15],
        [16], [17], [18], [], [], [], [], []][n]

#############################################################

def grafTab(player, n):
    M = set()
    if terminal(n): return M
    K = confTab[n]
    k = [0,0,0]
    for i in range(3):
        k[0],k[1],k[2] = K
        for j in grafCol(player, k[i]):
            k[i] = j
            M.add(confTabIds[k[0],k[1],k[2]])
    if len(M) == 0:
        M.add(n)
    #    print "passou aqui"
    return M

#############################################################

confCol = [ (i, j) 
   for i in range(5)
   for j in range(5)
   if i != j
]

confTab = [ (i, j, k)
   for i in range(20)
   for j in range(20)
   for k in range(20)
]

confTabIds = {it: i for i, it in enumerate(confTab)}

#############################################################

grafTab_ = [ # precalc of grafTab()
    [grafTab(0, i) for i in range(8000)],
    [grafTab(1, i) for i in range(8000)]
]

#############################################################

grafo = {}
for i in range(2):
    for j in range(8000):
        grafo[(i, j)] = []
        for k in grafTab_[i][j]:
            grafo[(i,j)].append((1-i,k))

#############################################################



import random

p = 0
q = 1263
i = 0

while not terminal(q):
    p, q = random.choice(grafo[(p, q)])
    print i, " ", 
    printTab(q)
    i += 1


print "ganhou", 
if terminal(q) == 1: 
    print " 0"
else:
    print " X"
    
    
    









