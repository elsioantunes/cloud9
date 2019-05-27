#!/usr/bin/python 
####################################################################
import sys

def input(t):
    a = sys.stdin.readline()
    if t: return a.split()
    return int(a)

####################################################################

def solve(l, r, n):
    
    if l > r: return 0
    m = n*n
    M = m + solve(l+1, r, 1)
    
    for i in range(l+1, r+1):
        if blocks[i] == blocks[l]:
            M = max(M, solve(l+1, i-1, 1) + solve(i, r, n+1)) 
    
    return M

####################################################################

for i in range(input(0)):
    nblocks = input(0)
    blocks = input(1)
    buf = {}
    print solve(0, nblocks-1, 1)
