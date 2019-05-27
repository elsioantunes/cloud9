'''
    Grafo do Dabriel
    https://www.urionlinejudge.com.br/judge/pt/problems/view/2768
    
'''


def getData():
    return map(int, raw_input().split())

n, m = getData()
for i in range(m):
    u, v, w = getData()

q = input()
for i in range(q):
    u, v, w = getData()

