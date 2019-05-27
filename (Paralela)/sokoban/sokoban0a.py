import random as rnd

class queue:
    def __init__(self):
        self.list = []
    
    def pop(self):
        return self.list.pop()

    def isNotEmpty(self):
        return len(self.list) != 0
        
    def show(self):
        print(self.list)

    ''' this is a fifo '''
    def push(self, item):
        self.list.insert(0, item)
        # for a lifo stack use append

def table():
    for j in range(h):
        for i in range(w):
            print (buf[w*j+i], end='\t')
        print('\n')

def solved(atual):
    return atual == r
    
def dirs(atual):
    ret = []
    for dx, dy, d in [(1, 0, 'r'),(-1, 0, 'l'),(0, 1, 'd'),(0, -1, 'u')]:
        x = atual%w
        y = ((atual-x)//w)%h
        if x+dx >= 0 and x+dx < w and y+dy >= 0 and y+dy < h:
            ret.append((x+dx+(y+dy)*w, d))
    return ret

w = 8
h = 7
buf = ['.']*w*h
r = rnd.randrange(0, w*h)
m = rnd.randrange(0, w*h)
buf[m] = 'C'
buf[r] = '0'


#print (dirs(m))
#dirs(m)
table()

        

def BFS():
    v = set()
    p = queue()
    p.push((m, []))
    while p.isNotEmpty():
        atual, path = p.pop()
        if solved(atual): return path
        if atual in v: continue
        for prox, d in dirs(atual):
            p.push((prox, path+[d]))
        v.add(atual)
            
            
        
    
        

print (BFS())
    