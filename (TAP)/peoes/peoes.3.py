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
    #    print "pq passou aqui tantas vezes?"
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
    for j in range(2000):
        grafo[(i, j)] = [[
            (1-i, k)
            for k in grafTab_[i][j]
        ],666]

#############################################################

'''
63 terminal conf's for 0
6737 6738 6739 6756 6757 6758 6759 6776 6777 6778 6779 6796 
6797 6798 6799 7136 7137 7138 7139 7156 7157 7158 7159 7176 
7177 7178 7179 7196 7197 7198 7199 7536 7537 7538 7539 7556 
7557 7558 7559 7576 7577 7578 7579 7596 7597 7598 7599 7936 
7937 7938 7939 7956 7957 7958 7959 7976 7977 7978 7979 7996 
7997 7998 7999

63 terminal conf's for 1
1684 1688 1692 1696 1764 1768 1772 1776 1844 1848 1852 1856 
1924 1928 1932 1936 3284 3288 3292 3296 3364 3368 3372 3376 
3444 3448 3452 3456 3524 3528 3532 3536 4884 4888 4892 4896 
4964 4968 4972 4976 5044 5048 5052 5056 5124 5128 5132 5136 
6484 6488 6492 6496 6564 6568 6572 6576 6644 6648 6652 6656 
6724 6728 6732

'''



#
'''

def DFS():
    pilha = []
    pilha.append((0,1263))
    while len(pilha):
        atual = pilha.pop()
        if terminal(atual):
            
            
        for sucessor in grafo[atual]:
            if sucessor in vis:
                
            else:
                pilha.append(sucessor)
                
#
'''


#'''
for estado in grafo:
    print estado
    for j in grafo[estado]:
        print j,
    print 
    print 

#'''



#
'''
for turn, conf in grafo:
    if terminal(conf) == 2 :
        print conf
        #printTab(conf)

#
'''




# (i, x) not in V.keys() means it was not visited
# V[(i, x)] = 1          means it is being visited
# V[(i, x)] = 2          means it has no winning strategy
# V[(i, x)] = 3          means it has a winning strategy

'''
def ganha(i, x):
    V[(i, x)] = 1
    
    if terminal(x): 
        V[(i, x)] = 2
        return
    
    for j, y in grafo[(i, x)]:
        if not (j, y) in V.keys(): ganha(j, y)
        if V[(j, y)] == 2:
            V[(i, x)] = 3
            
    if V[(i, x)] == 1:
        V[(i, x)] = 2
'''
    
    









