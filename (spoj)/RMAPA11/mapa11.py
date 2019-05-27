'''
    http://br.spoj.com/problems/RMAPA11/
    Reduzindo detalhes em um mapa
    http://br.spoj.com/problems/RMAPA11/
    algoritmo  "Prim" 
    Video que ajudou: https://www.youtube.com/watch?v=rsIlC0VeHew
                     https://www.youtube.com/watch?v=RXL8Z-HfdHQ
    
    similar: 
        br.spoj.com/problems/REDOTICA/ (resolvido com kruskal)
    
'''

def getData():
    return map(int, raw_input().split())

inf = 500
n, m = getData()

adj = {i:[] for i in range(n)}
v = [0]*n
d = [inf]*n

for i in range(m):
    x, y, p = getData()
    x -= 1; y -= 1
    adj[x] += [(y, p)]
    adj[y] += [(x, p)]

d[0] = 0
s = 0
j = 0

for k in range(n):
    mini = inf
    for i in range(n):
        if not v[i] and d[i] < mini:
            mini = d[i]
            j = i
    v[j] = 1
    
    for a in adj[j]:          # Prim, uh!
        i, p = a
        d[i] = min(d[i], p)

    s += mini
print s
