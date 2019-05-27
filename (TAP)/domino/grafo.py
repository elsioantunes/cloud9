




#!/usr/bin/python
import sys
def inputs():
    a, b = sys.stdin.readline().split()    
    return int(a), int(b)
########################################################################


def dfs(t):
    vis[t] = 1
    count[0] +=1
    for i in range(n):
        if adj[(t,i)] and not vis[i]:
            dfs(i)
            
        

n, k = inputs()
print n, k

adj = {}
vis = {}
count = [0]

for i in range(2*n):
    vis[i] = 0
    for j in range(2*n):
        adj[(i,j)] = 0

for i in range(n):
    a, b = inputs()
    print a, b
    adj[(a,b)] = 1
    adj[(b,a)] = 1


s = 0
for i in range(2*n):
    count[0] = 0
    if not vis[i]:
        dfs(i)
        s +=1
        for j in vis.values():
            print j,
        print count[0]
print s, ""


    
'''
for i in adj:
    print i, adj[i]
'''


