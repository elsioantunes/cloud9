'''
    Ir e vir
    https://www.urionlinejudge.com.br/judge/pt/problems/view/1128
    
    Objetivo
    Determinar se o grafo dado tem a caracteristica de ter um caminho 
    de 'a' para 'b' ou de 'b' para 'a' para qualquer par de vertices.
    
    Procedimento
    Este codigo usa (uma simplificacao do) algoritmo Kosaraju-Sharir 
    para determinar componentes fortes. Passando o DFS no grafo e no
    inverso dele e conferindo se ambos visitaram todos os vertices.
    Essa versao nao conta componentes. O retorno positivo so acontece
    se o grafo tiver um unico componente forte.

    Teoria sobre componentes fortes 
    https://www.ime.usp.br/~pf/algoritmos_em_grafos/aulas/forte.html
    https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/strong-comps.html
    https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/kosaraju.html
    https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/tarjan.html
    
    Similares?
    http://br.spoj.com/problems/OBIDOMIN/
    
'''

def getData():
    return map(int, raw_input().split())

def dfs(G, u):
    vis[u]=1
    for v in G[u]:
        if not vis[v]:
            dfs(G, v)
    
while 1:
    n, m = getData()    
    if not n: break
    adj1 = {i:[] for i in range(n)}
    adj2 = {i:[] for i in range(n)}
    for i in range(m):
        v, w, p = getData()
        v -= 1; w -= 1; p -= 1
        adj1[v] += [w]
        adj2[w] += [v]
        if p: 
            adj1[w] += [v]
            adj2[v] += [w]
    
    vis = [0]*n  #
    dfs(adj1, 0) # Kosaraju, uh!
    s = sum(vis) #
                 #        
    vis = [0]*n  #
    dfs(adj2, 0) #
    
    print 1 if s == sum(vis) and s == n else 0
