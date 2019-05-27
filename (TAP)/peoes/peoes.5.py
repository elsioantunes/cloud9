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

grafTab_ = [ # precalc of grafTab()   // nao acho necessario
    [grafTab(0, i) for i in range(8000)],
    [grafTab(1, i) for i in range(8000)]
]

#############################################################

grafo = {}
for i in range(2):
    for j in range(8000):
        grafo[(i, j)] = [[k for k in grafTab_[i][j]], 1-i, 666]

#############################################################

def DFS(estado):
    turno, atual = estado
    grafo[(turno, atual)][2] = 1
    if terminal(atual):
        grafo[(turno, atual)][2] = 2
        return
    
    sucessor, t, flag  = grafo[(turno, atual)]
    for i in sucessor:
        if grafo[(t, i)][2] == 666:
            DFS((t, i))
        
        if grafo[(t, i)][2] == 2:
            grafo[(turno, atual)][2] = 3
    
    if grafo[(turno, atual)][2] == 1:
        grafo[(turno, atual)][2] = 2

for i in range(2):
    for j in range(8000):
        if grafo[(i,j)][2] == 666:
            DFS((i, j))

#############################################################

def opcoes(player):
    M = []
    for i in grafo[(player, board)][0]:
        if grafo[(1-player, i)][2] == 2:
            M.insert(0, i)
        else:
            M.append(i)
    return M

#############################################################


board = 1263
p1 = 0
pc = 1


print opcoes(0)



#
'''
for i in grafo[(0, 1263)][0]:
    if grafo[(1, i)][2] == 2:
        print i
#
'''
    



'''
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

'''


'''
for i in confTabIds:
    print i, confTabIds[i]
'''





'''
# I dont understood this shit

import random
estrategi = [{},{}]
for player, conf  in grafo:
    if terminal(conf): continue
    M = set()
    v = confTab[conf]
    k = [0,0,0]
    for i in range(3):
        k[0], k[1], k[2] = v
        for j in grafCol(player, v[i]):
            k[i] = j
            M.add(confTabIds[k[0], k[1], k[2]])
    if len(M) == 0: M.add(conf)
    estrategi[player][conf] = random.choice(tuple(M)) 
    for i in M:
        if grafo[(1-player, i)][2] == 2:
            estrategi[player][conf] = i
            
        

print len(estrategi[0].keys())
for i in estrategi[0].keys():
    if grafo[(0, i)][2] == 3:
        print '+', 
    else:
        print '-', 
    
    print i, ': ', 
    
    if grafo[(1, estrategi[0][i])][2] == 3:
        print '+', 
    else:
        print '-', 
    print estrategi[0][i]

            
    

    
#'''    
    
    















