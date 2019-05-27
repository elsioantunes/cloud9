##############################################################

def solve(l, r, n):
    if l > r: return 0
    if (l, r, n) in buf: return buf[(l, r, n)]
    m = n*n
    M = m + solve(l+1, r, 1)
    for i in range(l+1, r+1):
        if blocks[i] == blocks[l]:
            M = max(M, solve(l+1, i-1, 1) + solve(i, r, n+1)) 
    buf[(l, r, n)] = M
    return M

for i in range(int(raw_input())):
    nblocks = int(raw_input())
    blocks = raw_input().split()
    buf = {}
    print "Case {0}: {1}".format(i+1, solve(0, nblocks-1, 1))

##############################################################