'''
 Ataque Programado
 https://www.urionlinejudge.com.br/judge/pt/problems/view/1792
 
 Objetivo: visitar todos os vertices em uma certa ordem
 Algoritmo: ordenacao topologica (algoritmo de Kahn)
 Similares: 
    Dudu Faz Servico (Dudu Service Maker)
    https://www.urionlinejudge.com.br/judge/pt/problems/view/1610
    
    Orkut
    http://br.spoj.com/problems/ORKUT/
    
    Escalonamento otimo
    http://br.spoj.com/problems/ESCALO11/

 Funcionamento:
    Para cada instancia, monta-se o grafo, anota os graus de entrada
    e os outros parametros e, aplica- se o algoritmo de Kahn 
    com uma fila de prioridade que minimiza inimigos e maximiza amigos.

'''
import heapq
class Node:
    def __init__(self):
        self.enemies = 0
        self.friends = 0
        self.grau = 0
        self.adj = []

class PriorityQueue:
    def  __init__(self):
        self.heap = []

    def push(self, node):
        entry = (node.enemies, 1.0/(node.friends+1), node)
        heapq.heappush(self.heap, entry)

    def pop(self):
        _, _, node = heapq.heappop(self.heap)
        return node

    def isEmpty(self):
        return len(self.heap) == 0

def getData():
    return map(int, raw_input().split())

def instancia(n, m, s, enemies, friends):
    # monta grafo
    G = {}
    for i in range(n):
        G[i] = Node()
        G[i].enemies = enemies[i]
        G[i].friends = friends[i]

    for i in range(m):
        x, y = getData()
        G[x-1].adj += [y-1]
        G[y-1].grau += 1    #
                            #
    pq = PriorityQueue()    #
    for i in range(n):      #   Kahn, uh! 
        if not G[i].grau:   #   O(n(lg n + m)) 
            pq.push(G[i])   #
                            # 
    while not pq.isEmpty(): #
        node = pq.pop()     #   
        if node.enemies >= s: break
        s += node.friends
        for i in node.adj:
            G[i].grau -=1
            if not G[i].grau:
                pq.push(G[i])
        n -= 1
    return n

# varias instancias
while 1:
    n, m, s = getData()
    if not n: break
    vis = {}
    enemies = getData()
    friends = getData()
    print "impossivel" if instancia(n, m, s, enemies, friends) else "possivel"

    
