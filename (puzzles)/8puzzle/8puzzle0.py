def showboard(state):
    for i, it in enumerate(state):
        if it : print (it, end=' ')
        else : print (' ', end=' ')
        if (i+1) % 3 == 0:
            print()
    print()

def _hash(state):
    h = 0
    for i in state:
        h = h*10 + i
    return h

def isGoal(state):
    return state == goal

def neigh(state):
    nb = []
    return nb
    

def bfs(state):
    c = 0
    v = set()
    f = [state]
    while f:
        c = c + 1
        atual = f.pop()
        if isGoal(atual): return c
        if _hash(atual) in v: continue
        
        for prox in neigh(atual):
            f = [prox] + f
        v.add(_hash(atual))
    return c
    
    
        
    


goal = [1, 2, 3, 4, 5, 6, 7, 8, 0]
state = [1, 2, 3, 4, 6, 0, 7, 5, 8]


showboard(state)
print (bfs(state))



