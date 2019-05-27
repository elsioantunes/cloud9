'''
 Dudu Faz Servico (Dudu Service Maker)
 https://www.urionlinejudge.com.br/judge/pt/problems/view/1610
 
 Objetivo: detectar ciclos
 Algoritmo: dfs
 Similares: 
    Ataque Programado. Mais dificil
    https://www.urionlinejudge.com.br/judge/pt/problems/view/1792
 
    Mais dificil. Precisa ordenacao topologica
    http://br.spoj.com/problems/ORKUT/
    
    Topologica, alfabetica e STDio
    http://br.spoj.com/problems/ESCALO11/

 Funcionamento:
    O dfs usa uma lista 'vis[]' que registra os estados
        0: branco, nao visitado
        1: cinza, visitado
        2: preto, finalizado
    Visita os vizinhos recursivamente. 
    Se encontrar marcado com 1 retorna verdadeiro (tem ciclo).
    Se nao tiver marcado visita, se marcado com 2 ignora.
    (precisa marcar com 2 - e nao com 0 - pra substituir a marcacao 1)
    
'''

def getData():
    return map(int, raw_input().split())

def dfs(G, u):
    vis[u] = 1
    for v in G[u]:
        if v not in vis:
            if dfs(G, v): return 1
        else: 
            if vis[v] == 1: return 1
    vis[u] = 2
    return 0

def instancia():
    # monta grafo
    n, m = getData()
    G = {i:[] for i in range(n)}
    for i in range(int(m)):
        x, y = getData()
        G[x-1] += [y-1]
    
    # percorre disconectos
    for i in range(n):
        if i not in vis:
            if dfs(G, i):
                return 1
    return 0

# varias instancias
for i in range(int(input())):
    vis = {}
    print "SIM" if instancia() else "NAO"
    
    
