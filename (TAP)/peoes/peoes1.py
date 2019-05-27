#!/usr/bin/python
import sys

'''
   Versao primeira do programa, que nao poda o grafo e nao joga com 5 peoes.
   O que eh uma pena, pq eu passei um bom tempo tentando implementar a outra
   versao, descobri varias coisas legais sobre algoritmos e listagens... mas,
   pelo fato de nao conseguir fazer funcionar a tempo, fica como licao.
   
   Devido a um comportamento estranho do tratamento de I/O do python que eu
   provavelmente ainda nao entendi por completo, o programa ainda pode 
   apresentar falhas. Por ex, aqui no cloud9 o python acusa erro ateh nos 
   comentarios, caso vc use caracteres acentuados. 


     testado com... ok (ganha sempre)
     ./competir  "python peoes1.py" ./gabarito
     
     testado com... ok (perde sempre)
     ./competir  ./gabarito  "python peoes1.py"
     
     testado com... ok (ganha sempre)
     ./competir  "python peoes1.py" ./aleatorio
     
     testado com... bugs :(
     (por favor, professor, se puder me mande um feedback)
     ./competir  ./aleatorio "python peoes1.py" 
     
        Juiz: declarando o segundo jogador como vencedor (motivo abaixo).
        Juiz: ultima jogada invalida.

     testado com... OK? 
     ./competir ./aleatorio ./aleatorio

'''


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
    return M

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

for i in range(2):
    for j in range(8000):
        if grafo[(i,j)][2] == 666:
            DFS((i, j))

#############################################################

def in2id(m, n):
    o = confTab[board]
    for i in opcoes(p1):
        for key, j in enumerate(confTab[i]):
            d = confCol[j][p1] - confCol[o[key]][p1]
            if d != 0:
                if m == key+1 and n == d:
                    return i
    return -1

#############################################################

def id2out(id):
    o = confTab[board]
    for i in opcoes(pc):
        for key, j in enumerate(confTab[i]):
            d = confCol[o[key]][pc] - confCol[j][pc]
            if d != 0:
                if id==i: return (key+1, d)
    return -1


board = 1263
p1 = 0
pc = 1


primeiro = "primeiro" in sys.argv

debug = 0

if(debug): printTab(board)

while 1:
    if not primeiro:
        m, n = sys.stdin.readline().split()    
        m = int(m)
        n = int(n)

        id = in2id(m, n)
        if(debug): printTab(id)
        board = id
        
        if terminal(id): break
    
    primeiro = 0

    id = opcoes(pc)[0] # a primeira opcao deve ser a melhor
    #print id2out(id)[0], id2out(id)[1]
    sys.stdout.write(str(id2out(id)[0]) + ' ' + str(id2out(id)[1]) + '\n')
    board = id
    if(debug): printTab(id)
    if terminal(id): break
