def table(level):
    for j, jt in enumerate(level):
        for i, it in enumerate(jt):
            print(it, end=' ')
        print('')

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
level = level.splitlines()


state = [0]

table(level)



def isWall(d):
    return level[d[0]][d[1]] == "#"

def dirs(atual):
    i, j = atual
    return [(i + 1, j),(i - 1, j),(i, j + 1),(i, j - 1)]

def neigh(atual):
    ng = []
    for d in dirs(atual[0]):
        if isWall(d): continue
        ng = ng + [d]
    return ng

def BFS2(state):
    c = []
    v = set()
    p = [state]
    while p:
        atual = p.pop()
        if atual in v: continue
        for prox in neigh(atual):
            p = [prox] + p
        v.add(atual)
        c = c + [atual[0]]
    return c


state = [0]
for i, line in enumerate(level):
    for j, ch in enumerate(line):
        if ch == "@": state[0] = (i, j)

print (BFS2(state))

table(level)




'''
     ####
    ##. ##
##### .  #
#   #  # #
# $ #  # #
# $  @   #
######  ##
     ####


Solution:
lluullddRRRRuruurrdddldlUUUUdddllluulDldRRRRuruurrdddldlUUU


http://www.sokobano.de/wiki/index.php?title=Optimizer

'''