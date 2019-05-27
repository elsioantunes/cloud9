col = [(j, 4-i)
    for i in range(5) 
        for j in range(5) 
            if 4-i != j
]

conf = [(i, j, k)
    for i in range(20) 
        for j in range(20) 
            for k in range(20) 
                #if i <= j and j <= k
]

def grafo_coluna(player, n):
    if player == 0:
        if n == 0: return [1,2,3]
        if n == 1: return [2,3]
        if n == 2: return [3]
        if n == 4: return [5,6]
        if n == 5: return [6]
        if n == 6: return [7]
        if n == 8: return [9]
        if n == 9: return [10]
        if n == 10: return [11]
        if n == 12: return [13]
        if n == 13: return [14,15]
        if n == 14: return [15]
        if n == 16: return [17,18,19]
        if n == 17: return [18,19]
        if n == 18: return [19]
    if player == 1:
        if n == 0: return [4,8,12]
        if n == 1: return [5,9]
        if n == 2: return [6]
        if n == 3: return [10]
        if n == 4: return [8,12]
        if n == 5: return [9]
        if n == 6: return [13]
        if n == 7: return [11,15,19]
        if n == 8: return [12]
        if n == 9: return [16]
        if n == 10: return [14,18]
        if n == 11: return [15,19]
        if n == 13: return [17]
        if n == 14: return [18]
        if n == 15: return [19]
    return []

def grafo_tabuleiro(player, n):
    K = conf[n]
    M = set()
    k = [0]*3
    for i in range(3):
        for m, it in enumerate(K):
            k[m] = it
        for j in grafo_coluna(player, k[i]):
            k[i] = j
            M.add((k[0],k[1],k[2]))
    return M

def terminal(conf):
    p0 = 0; p1 = 0
    if col[conf[0]][0] == 4 and col[conf[1]][0] == 4 and col[conf[2]][0] == 4: p0 = 1
    if col[conf[0]][1] == 0 and col[conf[1]][1] == 0 and col[conf[2]][1] == 0: p1 = 1
    return p1*2+p0



grafo = {}
for i in range(2):
    for j in range(8000): # 8000
        grafo[(i, j)] = []
        for k in grafo_tabuleiro(i, j):  # grafo_tabuleiro deveria estar retornando IDs
            grafo[(i, j)].append((1-i, k))





print grafo[(0,0)][0]

n = 10
while n:
    n -=1
    print n

    


'''
'''
        





'''
for i in conf:
    if terminal(i):
        print i, "ganhou ",terminal(i)-1
'''


'''
print conf[0]
print
for i, it in enumerate(grafo_tabuleiro(0, 0)):
    print i, it
'''



