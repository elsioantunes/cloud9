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

def item_swp(s, i):
    j = s[9]
    s[i], s[j] = s[j], s[i]
    s[9] = i
    
def valid(j):
    mv = []
    if j % 3 > 0: mv += [j - 1]
    if j % 3 < 2: mv += [j + 1]
    if j / 3 > 0: mv += [j - 3]
    if j / 3 < 2: mv += [j + 3]
    return mv
    
def neigh(state):
    j = state[9]    
    nb = []
    for i in valid(j):
        s = state[:]
        item_swp(s, i)
        nb += [(s, i)]    
    return nb

def bfs(state):
    v = set()
    f = [[state, []]]
    while f:
        atual, path = f.pop()
        if isGoal(atual): return path
        if _hash(atual) in v: continue        
        v.add(_hash(atual))
        for prox, p in neigh(atual):
            f = [[prox, path + [p]]] + f
    return 666

goal = [1, 2, 3, 4, 5, 6, 7, 8, 0, 8]
state = [1, 2, 3, 4, 6, 0, 7, 5, 8, 5]

showboard(state)
    
print (bfs(state))



