def printb():
    for i in b:
        if i: 
            print "#",
        else :
            print '.',
    print

def UP(c, bb, pp):
    bb[c] ^= 1
    if pp[c] != c:
        UP(pp[c], bb, pp)

def DOWN(u):
    for v in G[u]:
        b[v] ^= 1
        DOWN(v)


'''
    testa um monte de possibilidades
    se existir um algoritmo especifico pra isso, professor
    por favor, joga no tidia pra gente ver?
    independente da disciplina, queremos saber a forma correta 
'''
def ksubsets(nn, bb, k, C, pp):
    global ret
    if nn == 0:
        for i, it in enumerate(C):
            if it:
                UP(i,bb,pp)

        if sum(bb) == 0: 
            ret = 1

        for i, it in enumerate(C):
            if it:
                UP(i,bb,pp)

    if nn > k:
        C[nn-1] = 0
        ksubsets(nn-1, bb, k, C, pp)
    
    if k > 0:
        C[nn-1] = 1
        ksubsets(nn-1, bb, k-1, C, pp)
    


# entrada
n = input() # numero de vertices
p = [int(i) for i in raw_input().split()] # lista de pais
b = [1 if int(i) > 0 else 0 for i in raw_input().split()] # lista de bits

# grafo (arvore) a partir da lista de pais
G = {i:[] for i in range(n)}
for i, it in enumerate(p):
    if i != it:
        G[it] += [i]
    




ret = 0
def arv(nn, bb, pp):
    C = [7]*nn
    ret = 0
    ksubsets(nn, bb, 3, C, pp)
    
    

arv(n, b, p)
print ret




'''
printb()
print
#b = [1]*n
b_ = tuple(b)

for i in range(3):
    for j in range(n):
        UP(j)
        printb()
        UP(j)
        
    for j in range(n):
        DOWN(j)
        if b_ == tuple(b): continue
        printb()
        DOWN(j)
    print
'''
    

