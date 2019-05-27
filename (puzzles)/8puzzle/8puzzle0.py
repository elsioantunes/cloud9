def showboard(state):
    for i in range(9):
        if state[i] : print (state[i], end=' ')
        else : print (' ', end=' ')
        if (i+1) % 3 == 0:
            print()
    print()

def _hash(state):
    h = 0
    for i in range(8):
        h = h*10 + state[i]
    return h

def isGoal(state):
    return state == goal

def item_swp(s, i, j):
    s[i], s[j] = s[j], s[i]
    s[9] = i
    

def neigh(state):
    nb = []
    valid = [[1, 3], [0, 2, 4],[1, 5], 
            [0, 4, 6], [1, 3, 5, 7], [2, 4, 8],
            [3, 7], [4, 6, 8], [5, 7]]
    
    j = state[9]
    for i in valid[j]:
        s = state[:]
        item_swp(s, i, j)
        nb.append((s, i))
    return nb


def bfs(state):
    v = set()
    f = [[state, []]]
    while f:
        atual, path = f.pop()
        if isGoal(atual): return path
        if _hash(atual) in v: continue
        
        for prox, p in neigh(atual):
            f = [[prox, path + [p]]] + f
        v.add(_hash(atual))
    return 666

goal = [1, 2, 3, 4, 5, 6, 7, 8, 0, 8]
state = [1, 2, 3, 4, 6, 0, 7, 5, 8, 5]

showboard(state)
    
print (bfs(state))



