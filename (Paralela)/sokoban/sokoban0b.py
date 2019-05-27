import random as rnd

def table():
    for j, jt in enumerate(wall):
        for i, it in enumerate(jt):
            print(it, end=' ')
        print('')

def solved(atual):
    return atual == r

def pos(atual, dx, dy):
    x = atual%w + dx
    y = ((atual-atual%w)//w)%h + dy
    return x, y
    
    
def successors(atual):
    ret = []
    for dx, dy, d, D in dirs:
        x, y = pos(atual, dx, dy)
        if wall[y][x] != "#":
            ret.append((x+(y)*w, d))
    return ret

def BFS():
    v = set()
    p = [(m, [])]
    while p:
        atual, path = p.pop()
        if solved(atual): return path
        if atual in v: continue
        for prox, d in successors(atual):
            p = [(prox, path+[d])]+p
        v.add(atual)
        


dirs = [(1, 0, 'r', 'R'),(-1, 0, 'l', 'L'),(0, 1, 'd', 'D'),(0, -1, 'u', 'U')]
w = 7
h = 8
buf = ['.']*w*h
r = rnd.randrange(0, w*h-1)+1
m = rnd.randrange(0, w*h-1)+1
buf[m] = '@'
buf[r] = '0'

level = """\
#######
#     #
#     #
#. #  #
#. $$ #
#.$$  #
#.#  @#
#######"""

level = """\
#######
#    @#
# #####
#     #
#   # #
#   #$#
#   #.#
#######"""
wall = level.splitlines()


table()
print (BFS())
    